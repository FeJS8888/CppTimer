#include<bits/stdc++.h>
#include "FeEGELib.h"
using namespace std;
using namespace FeEGE;

char s[1025];

int main(){
	setcaption("��ʱ��");
	initgraph(600,400);
	initpen();
	pen::font(80,"��Բ");
	
	auto trans = [&](const string& raw){
		if(raw.length() <= 1) return "0" + raw;
		return raw;
	};
	
	function<void(int)> func;
	function<void(void)> F;
	func = [&](int rest){
		pen::clear_all();
		if(rest == -1){
			string str = "ʱ�䵽";
			int w = textwidth(str.c_str(),pen_image);
			int h = textheight(str.c_str(),pen_image);
			pen::print(((X - w) >> 1),((Y - h - 100) >> 1),str);
			
			pen::font(30,"��Բ");
			str = "�������λ������";
			w = textwidth(str.c_str(),pen_image);
			h = textheight(str.c_str(),pen_image);
			pen::print(((X - w) >> 1),((Y + 100 - h) >> 1),str);
			reflush();
			
			globalListen(EventType.frame,"click",[=](){
				if(!getkey(LeftButton)) return;
				push_schedule([=,&F](){
					F();
					stopGlobalListen(EventType.frame,"click");
				});
			});
			
			return;
		}
		string str = trans(to_string(rest / 60)) + " : " + trans(to_string(rest % 60));
		int w = textwidth(str.c_str(),pen_image);
		int h = textheight(str.c_str(),pen_image);
		pen::print(((X - w) >> 1),((Y - h) >> 1),str);
		setTimeOut([=,&func](){
			func(rest - 1);
		},1000);
	};
	
	F = [&](){
		delay_ms(100);
		pen::font(80,"��Բ");
		inputbox_getline("����ʱ��",
	                    "����Ϊ��λ",
	                    s,
	                    sizeof(s)/sizeof(*s));
	    
	    int times = -1;
		sscanf(s,"%d",&times);
		
		func(times);
	};
	
	F();
	
	start();
	return 0;
}
