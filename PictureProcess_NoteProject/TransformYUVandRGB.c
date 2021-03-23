#include <stdio.h>
//
int Sample_yuv420Separation(char *name,int h,int w)
{
	FILE *err;
	FILE *fp = fopen(name,"rb+");
	if(fp == NULL)
	{
		perror("fopen error!:");
		exit(1);
	}
	FILE *fp_y = fopen("ouotput420_y.yuv","wb+");
		if(fp_y == NULL)
	{
		perror("fopen fp_y error!:");
		exit(1);
	}
	FILE *fp_u = fopen("ouotput420_u.yuv","wb+");
		if(fp_u == NULL)
	{
		perror("fopen fp_u error!:");
		exit(1);
	}
	FILE *fp_v = fopen("ouotput420_v.yuv","wb+");
		if(fp_v == NULL)
	{
		perror("fopen fp_v error!:");
		exit(1);
	}

	char *pic = (char *)malloc(w*h*3/2);//w*h(Y)+w*y*0.5(UV)= w*h*3/2
	err = fread(pic,1,w*h*3/2,fp);
	if(err == NULL)
	{
		perror("fread err:");
		exit(1);
	}
	err = fwrite(pic,1,w*h,fp_y); // (w*h/3*2)
	if(err == NULL)
	{
		perror("fwrite fp_y err:");
		exit(1);
	}
	err = fwrite(pic+w*h,1,w*h/4,fp_u);
	if(err == NULL)
	{
		perror("fwrite fp_u err:");
		exit(1);
	}
	err = fwrite(pic+w*h*5/4,1,w*h/4,fp_v);
	if(err == NULL)
	{
		perror("fwrite fp_v err:");
		exit(1);
	}
	
	free(pic);
	fclose(fp);
	fclose(fp_y);
	fclose(fp_u);
	fclose(fp_v);

	return 0;
}

//separate the RGB
int separate_RGB24(char *name,int w,int h)
{
	FILE* fp = fopen(name,"rb+");
  	FILE *fp1=fopen("output_r.y","wb+");
	FILE *fp2=fopen("output_g.y","wb+");
	FILE *fp3=fopen("output_b.y","wb+");

	unsigned char *pic=(unsigned char*)malloc(w*h*3);
	fread(pic,1,w*h*3,fp);
	for(int j=0,j<w*h*3,j=j+3){
		fwrite(pic+j,1,1,fp1);
		fwrite(pic+j+1,1,1,fp2);
		fwrite(pic+j+2,1,1,fp2);
	}
	free(pic);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	return 0;
}


unsigned char clip_value(unsigned char x,unsigned char min_val,unsigned char  max_val){
	if(x>max_val){
		return max_val;
	}else if(x<min_val){
		return min_val;
	}else{
		return x;
	}
}
 
//RGB to YUV420
bool RGB24_TO_YUV420(unsigned char *RgbBuf,int w,int h,unsigned char *yuvBuf)
{
	unsigned char*ptrY, *ptrU, *ptrV, *ptrRGB;
	memset(yuvBuf,0,w*h*3/2);
	ptrY = yuvBuf;
	ptrU = yuvBuf + w*h;
	ptrV = ptrU + (w*h*1/4);
	unsigned char y, u, v, r, g, b;
	for (int j = 0; j<h;j++){
		ptrRGB = RgbBuf + w*j*3 ;
		for (int i = 0;i<w;i++){
			
			r = *(ptrRGB++);
			g = *(ptrRGB++);
			b = *(ptrRGB++);
			y = (unsigned char)( ( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16  ;          
			u = (unsigned char)( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128 ;          
			v = (unsigned char)( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128 ;
			*(ptrY++) = clip_value(y,0,255);
			if (j%2==0&&i%2 ==0){
				*(ptrU++) =clip_value(u,0,255);
			}
			else{
				if (i%2==0){
				*(ptrV++) =clip_value(v,0,255);
				}
			}
		}
	}
	return true;
}
 
int simplest_rgb24_to_yuv420(char *url_in, int w, int h,int num,char *url_out){
	FILE *fp=fopen(url_in,"rb+");
	FILE *fp1=fopen(url_out,"wb+");
 
	unsigned char *pic_rgb24=(unsigned char *)malloc(w*h*3);
	unsigned char *pic_yuv420=(unsigned char *)malloc(w*h*3/2);
 
	for(int i=0;i<num;i++){
		fread(pic_rgb24,1,w*h*3,fp);
		RGB24_TO_YUV420(pic_rgb24,w,h,pic_yuv420);
		fwrite(pic_yuv420,1,w*h*3/2,fp1);
	}
 
	free(pic_rgb24);
	free(pic_yuv420);
	fclose(fp);
	fclose(fp1);
 
	return 0;
}



