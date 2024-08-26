#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//存放图片的颜色点阵数据RGB
char src1[1000][1000][3];
char src2[1000][1000][3];
char dst[1000][1000][3];

//位图文件头
struct bfHead
{
    char bfType[2]; //检查读入的文件是否是"BM"类型
	long bfSize;
	long bfReserved;
	long bfOffBits;
};

//位图信息头
struct biHead
{
	long biSize;
	long biWidth;   //图的宽度
	long biHeight;  //图的高度
	short biPlanes;
	short biBitCount;   //像素点位深度，24则为24位真彩图
	long biCompression;
	long biSizeImage;
	long biXPelsPerMeter;
	long biYpelsPerMeter;
	long biClrUsed;
	long biClrImportant;
};

int main(int argc, char* argv[])
{
    struct bfHead bfSrc1, bfSrc2;
    struct biHead biSrc1, biSrc2;

    //打开2个原始文件 供读取数据
    FILE *fp1 = fopen(argv[1], "r+b");
    FILE *fp2 = fopen(argv[3], "r+b");

    //混合的百分比，例如输入 80% 则percent为0.8
    double percent = 0;
    int i; 
    for (i = 0; i < strlen(argv[2]) - 1; ++i)
        percent = percent * 10 + (argv[2][i] - '0');
    percent /= 100;

    //打开目标文件 供写入数据
    //这个文件可能是没有的，fopen会创建一个新的文件；如果该文件已经存在，fopen会将其覆盖掉
    FILE *fp3 = fopen(argv[4], "w+b");

    //读取位图文件头 位图信息头
    fread(&bfSrc1, 14, 1, fp1);
    fread(&bfSrc2, 14, 1, fp2);
    fread(&biSrc1, 40, 1, fp1);
    fread(&biSrc2, 40, 1, fp2);

    //检查是否为BM类型 是否为24位真彩图 照片尺寸是否相等
    if (bfSrc1.bfType[0]=='B'&& bfSrc1.bfType[1]=='M' && bfSrc2.bfType[0]=='B' && bfSrc2.bfType[1]=='M'
        && biSrc1.biBitCount == 24 && biSrc2.biBitCount == 24
        && biSrc1.biWidth == biSrc2.biWidth && biSrc1.biHeight == biSrc2.biHeight)
    {
        //读取颜色点阵数据
        //遍历列 从下向上
        int y;
        for ( y = biSrc1.biHeight - 1; y >= 0; --y)
        {
            //遍历行 从前向后
            int x;
            for (x = 0; x < biSrc1.biWidth; ++x)
            {
                //文件数据流中按照BGR的顺序存储，我们以RGB的顺序存储
                int k;
				for (k = 2; k >= 0; --k)
                {
                    fread(&src1[x][y][k], 1, 1, fp1);
                    fread(&src2[x][y][k], 1, 1, fp2);
                }
            }
        }

        //混合像素到目标文件数据
        for (y = biSrc1.biHeight - 1; y >= 0; --y)
        {
            int x;
			for (x = 0; x<biSrc1.biWidth; ++x)
            {
                int k;
				for (k = 2; k >= 0; --k)
                    dst[x][y][k] = src1[x][y][k] * percent + src2[x][y][k] * (1 - percent);
            }
        }

        //写目标文件
        fwrite(&bfSrc1,14,1,fp3);
        fwrite(&biSrc1,40,1,fp3);
//        int y;
        for (y = biSrc1.biHeight - 1; y >= 0; --y)
        {
            int x;
			for (x = 0; x<biSrc1.biWidth; ++x)
            {
                int k;
				for ( k = 2; k >= 0; --k)
                    fwrite(&dst[x][y][k], 1, 1, fp3);
            }
        }

        printf("执行成功\n");
    }

    //关闭文件
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return 0;
}

