using UnityEngine;
using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Text;
using System.Collections;

public class TcpManager : MonoBehaviour {

	public UIButton ConnectButton;
	public UILabel ConnectLabel;
	public UILabel Infos;
	public UIButton RedButton;
	public UIButton GreenButton;
	public UIButton YellowButton;
	public UIButton BlueButton;
	public UIButton WhiteButton;
	bool isConnected = false;
	Socket wifiSocket;
	float countDownSecond = 60.0f*5;

	// Use this for initialization
	void Start () 
	{

	}
	
	// Update is called once per frame
	void Update () 
	{
		if(isConnected == true)
		{
			countDownSecond -= Time.deltaTime;
			ShowCountDownInfo();
			if(countDownSecond<=0.0f)
				DisconnectWifiShield();
		}
	}

	public void DisconnectWifiShield()
	{
		if(wifiSocket != null){
			wifiSocket.Shutdown(SocketShutdown.Both);
			wifiSocket.Close();	
		}

		wifiSocket = null;
		
		if(ConnectLabel != null)
			ConnectLabel.text = "Connect...";

		if(Infos != null)
			Infos.text = "Click button to connect...";
		isConnected = false;
	}

	void ShowCountDownInfo()
	{
		int mins = ((int)countDownSecond)/60;
		int seconds = ((int)countDownSecond) - (mins*60);

		string message = String.Format("Connected.\nWill disconnect in {0} mins, {1} seconds.", mins, seconds);
		if(Infos != null)
			Infos.text = message;


	}

	public void ConnectWifiShield()
	{
		//定义主机的IP及端口
		IPAddress ip = IPAddress.Parse("192.168.88.34");
		IPEndPoint ipEnd = new IPEndPoint(ip, 8899);
		//定义套接字类型
		wifiSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
		//尝试连接
		try
		{
			wifiSocket.Connect(ipEnd);
		}
		//异常处理
		catch (SocketException e)
		{
			if(Infos != null)
				Infos.text = "Fail to connect server...";
			Console.Write("Fail to connect server");
			Console.Write(e.ToString());
			return;
		}

		if(ConnectLabel != null)
			ConnectLabel.text = "Disconnect...";

		isConnected = true;
		countDownSecond = 60.0f*5;


	}

	public void ConnectButtonClicked()
	{
		if(isConnected == false)
			ConnectWifiShield();
		else
			DisconnectWifiShield();
	}

	public void SendStringData(string stringdata)
	{
		if (isConnected == false || wifiSocket == null)
			return;

		byte[] data = new byte[1024];
		//将从键盘获取的字符串转换成整型数据并存储在数组中    
		data = Encoding.ASCII.GetBytes(stringdata);
		//发送该数组
		wifiSocket.Send(data, data.Length, SocketFlags.None);
		countDownSecond = 60.0f*5;
	}

	public void RedButtonClicked()
	{
		SendStringData("RedButton");
	}

	public void GreenButtonClicked()
	{
		SendStringData("GreenButton");
	}

	public void YellowButtonClicked()
	{
		SendStringData("YellowButton");
	}

	public void BlueButtonClicked()
	{
		SendStringData("BlueButton");
	}

	public void WhiteButtonClicked()
	{
		SendStringData("WhiteButton");
	}

}
