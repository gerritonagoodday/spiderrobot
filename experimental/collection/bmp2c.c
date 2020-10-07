#include <stdio.h>
#include <string.h>
#include <malloc.h>

unsigned char *read_bmp(char *fname,int* _w, int* _h)
{
  unsigned char head[54];

  // From definition given by http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
  struct Header { // 14 bytes total
    Signature   char[2];
    FileSize    char[4];
    reserved    char[4];
    DataOffset  char[4];
  } header;

  struct InfoHeader {  // 40 bytes total
    Size        char[4];
    Width       char[4];
    Height      char[4];
    Planes      char[2];
    BPP         char[2];  // Bits per Pixel - important!
    Compression char[4];
    ImageSize   char[4];
    XpM         BYTE[4];
    YpM         BYTE[4];
    Important   BYTE[4];  // not actually important
  } info;

  FILE *f = fopen(fname,"rb");
  fread(header, 1, 14, f);
  fseek(f,14,SEEK_SET);
  fread(info,1,44,f);
  fseek(f,40,SEEK_CUR);

  if(info.BPP < 9){
  
  }


  int w = info.Width[0]  + ( ((int)info.Width[1]) << 8)  + ( ((int)info.Width[2]) << 16)  + ( ((int)info.Width[3]) << 24);
  int h = info.Height[0] + ( ((int)info.Height[1]) << 8) + ( ((int)info.Height[2]) << 16) + ( ((int)info.Height[3]) << 24);
  printf("Image size: W:%d   H:%d\n", w, h);

  // lines are aligned on 4-byte boundary
  int lineSize = (w / 8 + (w / 8) % 4);
  int fileSize = lineSize * h;

  unsigned char *img = malloc(w * h), *data = malloc(fileSize);

  // skip the header
  fseek(f,54,SEEK_SET);

  

  // skip palette - two rgb quads, 8 bytes
  fseek(f, 8, SEEK_CUR);

  // read data
  fread(data,1,fileSize,f);

  // decode bits
  int i, byte_ctr, j, rev_j;
  for(j = 0, rev_j = h - 1; j < h ; j++, rev_j--) {
    for( i = 0; i < w; i++) {
      byte_ctr = i / 8;
      unsigned char data_byte = data[j * lineSize + byte_ctr];
      int pos = rev_j * w + i;
      unsigned char mask = 0x80 >> i % 8;
      img[pos] = (data_byte & mask ) ? 1 : 0;
    }
  }

  free(data);
  *_w = w; *_h = h;
  return img;
}

int main(int argc, char *argv[])
{
  if(argc != 2){
    printf("Usage: %s bitmapfilename\n\n", argv[0]);
    return 1;
  }

  int w, h, i, j;
  unsigned char* img = read_bmp(argv[1], &w, &h);

  for(j = 0 ; j < h ; j++)
  {
        for(i = 0 ; i < w ; i++)
            printf("%c ", img[j * w + i] ? '0' : '1' );

        printf("\n");
  }

  return 0;
}
