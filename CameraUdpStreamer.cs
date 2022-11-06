//ReadMe
//author:Pilot.Phil
//time:2022-04-23
//作用：将unity3D中camera的画面通过RenderTexture读取bytes的方式，经过UDP协议发送，使得其他程序使用相同协议接收图片数据
//对象：应作为一个camera的component
//
//参考1：https://blog.csdn.net/qq_34907362/article/details/119864856
//Unity Sockect实现画面实时传输
//
//参考2：https://cloud.tencent.com/developer/article/1681722
//C#教程之C#中使用UDP通信实例
//
//上面的是TCP协议发送的
//由于TCP协议比UDP协议慢
//并且仅设计在本机内本地通信
//可以忽略udp的掉包问题
//改写为udp模式
//提高了性能，也简化了代码

//python 解码bytes到图片 例程：
//import socket
//import cv2
//import numpy as np

//s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
//# 绑定端口:
//s.bind(('127.0.0.1', 8848))
//while True:
// # 接收数据:
// data = s.recv(50000)
// # 解码
// nparr = np.fromstring(data, np.uint8)
// img_decode = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
// cv2.imshow('result', img_decode)
// cv2.waitKey(10)


using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using UnityEngine;

using Pilot.Attributes;


public class CameraUdpStreamer : MonoBehaviour
{
    UdpClient client;
    IPEndPoint remotePoint = null;

    [ReadOnly]
    public Camera cam;
    RenderTexture renderTexture = null;
    Texture2D texture2D = null;

    /// <summary>
    /// IP地址
    /// </summary>
    public string IP = "127.0.0.1";

    /// <summary>
    /// 端口
    /// </summary>
    public uint Port = 8848;

    /// <summary>
    /// 视频传输的质量
    /// </summary>
    [Range(1, 100)]
    public int Quality = 50;

    /// <summary>
    /// 显示调试打印信息
    /// </summary>
    public bool _debug = false;

    /// <summary>
    /// 图像发送的频率
    /// </summary>
    [Range(1, 60)]
    public uint Freq = 15;

    private double interval;

    void Start()
    {
        //1.初始化udp
        IPAddress remoteIP = IPAddress.Parse(IP);
        remotePoint = new IPEndPoint(remoteIP, (int)Port);
        client = new UdpClient();

        //2.相机的相关初始化
        renderTexture = new RenderTexture(Screen.width, Screen.height, 24);
        renderTexture.enableRandomWrite = true;
        cam = this.GetComponent<Camera>();//获取对象上的相机组件
        cam.targetTexture = renderTexture;
        texture2D = new Texture2D(Screen.width, Screen.height, TextureFormat.RGB24, false);

        interval = 1.0 / Freq;
    }

    private void FixedUpdate()
    {
        //this.SendTextureAsync();
        if (interval > 0)
        {
            Debug.Log(interval);
            interval -= Time.deltaTime; 
        }
        else
        {
            this.SendTextureAsync();
            interval = 1.0 / Freq;
        }
    }

    /// <summary>
    /// 异步的图像发送方法
    /// </summary>
    /// <returns></returns>
    private async Task SendTextureAsync()
    {
        // 读取屏幕像素进行渲染
        RenderTexture.active = renderTexture;
        texture2D.ReadPixels(new Rect(0, 0, renderTexture.width, renderTexture.height), 0, 0);
        RenderTexture.active = null;

        //编码成jpg
        byte[] bytes = texture2D.EncodeToJPG(Quality);

        await client.SendAsync(bytes, bytes.Length, remotePoint);

        if (_debug) Debug.Log(this.name + " SendTextureAsync OK");
    }

    /// <summary>
    /// 程序退出时关闭udp连接
    /// </summary>
    private void OnApplicationQuit()
    {
        client?.Close();

        if (_debug) Debug.Log(this.name + " UDP client close");
    }
}
