//#include<iostream>
//#include<stdio.h>
//#include<conio.h>
//#include<sstream>
//#include"RakNetController.h"
//
//static RakNetController rn = RakNetController();
//
//int Initialize(int argc, char* argv[]) 
//{
//	if (argc == 1)
//	{
//		return -1;
//	}
//
//	if (strcmp(argv[1], "server") == 0) 
//	{ 
//		if ((!rn.Initialize()) || (!rn.CreateServer(27015))) 
//		{ 
//			return -1; 
//		} 
//	}
//	else if(strcmp(argv[1], "client") == 0) 
//	{ 
//		if ((!rn.Initialize()) || (!rn.CreateClient("127.0.0.1", 27015))) 
//		{ 
//			return -1; 
//		} 
//	}
//	else return - 1; 
//
//	return 0; 
//}
//
//void GameLoop() 
//{ 
//	while (true) 
//	{ 
//		char key = ' '; 
//		std::stringstream ss; 
//		while ((key != '\r') && (key != 27))
//		{ 
//			if (_kbhit()) 
//			{ 
//				key = _getch(); 
//				ss << key; 
//				printf("%c", key); 
//			}
//			rn.RecvData(); 
//		}
//		if (key == 27) 
//			break; 
//
//		rn.SendData(ss.str().c_str()); 
//	} 
//}

//int main(int argc, char* argv[])
//{
//	int retValue = Initialize(argc, argv);
//	if (retValue == 0)
//	{
//		GameLoop();
//		rn.Cleanup();
//	}
//	return retValue;
//}