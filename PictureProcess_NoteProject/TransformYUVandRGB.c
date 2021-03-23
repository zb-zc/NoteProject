#include <stdio.h>
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

