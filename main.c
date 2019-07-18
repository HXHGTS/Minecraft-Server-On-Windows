#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
int main() {
	int show,boardcast,java_install,server_install;
	errno_t ret1,ret2,ret3,ret4,ret5;
	char mc[200], run[300];
	char eula[11] = "eula=true\n";
	char token[17] = "4aae5c0065df7847";
	FILE* fp1, * fp2, * fp3, * fp4,*fp5;
	java_install = 0;
	system("title Minecraft服务器搭建工具");
	system("color 0A");
	printf_s("-------------------------------------------------------\n");
	printf_s("-----------------Minecraft服务器搭建工具---------------\n");
	printf_s("-------------------------------------------------------\n");
	ret5 = fopen_s(&fp5, "jre-8u211-windows-x64.exe", "r");
	if (ret5) {
		printf_s("正在下载JAVA环境. . .\n");
		system("start aria2c -x16 https://sdlc-esd.oracle.com/ESD6/JSCDL/jdk/8u211-b12/478a62b7d4e34b78b671c754eaaf38ab/jre-8u211-windows-x64.exe?GroupName=JSC&FilePath=/ESD6/JSCDL/jdk/8u211-b12/478a62b7d4e34b78b671c754eaaf38ab/jre-8u211-windows-x64.exe&BHost=javadl.sun.com&File=jre-8u211-windows-x64.exe&AuthParam=1560937839_07f2a32d5785ea19ccd900ebece3ddb2&ext=.exe");
		printf_s("正在安装JAVA环境. . .\n");
		system("start jre-8u211-windows-x64.exe");
	}
	else {
		java_install = system("\"C:\\Program Files\\Java\\jre1.8.0_211\\bin\\java.exe\" -version");
		if (java_install != 0) {
			printf_s("正在安装JAVA环境，安装完成请重启本软件！\n");
			system("start jre-8u211-windows-x64.exe");
		}
	}
	printf_s("Notice:请将本软件放置在MC服务器文件同级目录下！\n");
	printf_s("-------------------------------------------------------\n");
	ret3 = fopen_s(&fp3, "server.jar", "r");
	if (ret3) {
		printf_s("请将MC国际版文件拖拽至本窗口(下方出现路径说明拖拽成功，若希望从官网下载请输入d)：\n");
		scanf_s("%s", mc,200);
		if (mc[0] == 'd' || mc[0] == 'D') {
			system("aria2c -x16 https://launcher.mojang.com/v1/objects/808be3869e2ca6b62378f9f4b33c946621620019/server.jar");
			sprintf_s(mc,11, "server.jar");
		}
	}
	else {
		printf_s("已检测到MC国际版服务器jar文件,无需设置路径！\n");
		sprintf_s(mc,11, "server.jar");
	}
	ret2 = fopen_s(&fp2, "server.properties", "r");
	if (!ret2) {
		fclose(fp2);
		printf_s("游戏配置文件已存在，可在弹出页中修改！\n");
		printf_s("-------------------------------------------------------\n");
		printf_s("是否弹出配置文件以供修改？是=1，否=2, 恢复默认=3：");
		scanf_s("%d", &show);
		if (show == 1) {
			system("notepad server.properties");
		}
		else if (show == 3) {
			printf("已恢复默认配置. . .\n");
			system("del server.properties");
		}
	}
	else {	
		printf_s("未找到游戏配置文件，将采用默认配置，下次启动时可在弹出页中修改！\n");
	}
	ret1 = fopen_s(&fp1, "eula.txt", "r");
	if (ret1) {
		fopen_s(&fp1, "eula.txt", "w");
		fprintf_s(fp1, "%s", eula);
		fclose(fp1);
	}
	printf_s("-------------------------------------------------------\n");
	printf_s("是否建立外发服务器？是=1，否=2：");
	scanf("%d", &boardcast);
	printf_s("\n-------------------------------------------------------\n");
	system("cls");
	printf_s("-------------------------------------------------------\n");
	printf_s("------正在搭建服务器,按Ctrl+C暂停,输入help获得帮助-----\n");
	printf_s("-------------------------------------------------------\n\n\n");
	ret4 = fopen_s(&fp4, "natapp.exe", "r");
	if (!ret4&&boardcast==1) {
		printf_s("----------------正在搭建外网转发服务器-----------------\n\n\n");
		sprintf_s(run,45,"start natapp --authtoken=%s",token);
		system(run);
	}
	printf_s("-------------------------------------------------------\n");
	printf_s("-----------------正在搭建MC本地服务器------------------\n");
	printf_s("--------------本地服务器:127.0.0.1:25565---------------\n");
	printf_s("-------------------------------------------------------\n");
	sprintf_s(run, 300, "\"C:\\Program Files\\Java\\jre1.8.0_211\\bin\\java.exe\" -Xmx1024M -Xms1024M -jar %s nogui", mc);
	system(run);
	system("pause");
	return 0;
}