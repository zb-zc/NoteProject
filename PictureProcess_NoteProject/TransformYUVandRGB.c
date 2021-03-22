#include <stdio.h>
int Sample_yuv420Separation(char *name,int h,int w)
{
	FILE *fp = fopen(name,"rb+");
	FILE *fp_y = fopen("ouotput420_y.y","wb+");
	FILE *fp_u = fopen("ouotput420_u.y","wb+");
	FILE *fp_v = fopen("ouotput420_v.y","wb+");

	char *pic = (char *)malloc(w*h/3*2);
	fread(pic,1,w*h/3*2,fp);
	fwrite(pic,1,w*h,fp_y); // (w*h/3*2)
	fwrite(pic+w*h,1,w*h/4,fp_u);
	fwrite(pic+w*h*5/4,1,w*h/4,fp_v);
	
	free(pic);
	fclose(fp);
	fclose(fp_y);
	fclose(fp_u);
	fclose(fp_v);

	return 0;
}


int main(int argc,char *argv)
{
printf("-----%s-----%d-----%d----\n",argv[1],argv[2],argv[3]);
Sample_yuv420Separation(argv[1],(int)argv[2],(int)argv[3]);
return 0;
}