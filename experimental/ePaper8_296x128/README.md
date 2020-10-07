# Headline

Create a C header-file that contains a C-array of the bitmap file's content.

# Synopsys

Embedded displays do not have the sophisticated graphical display abstractions
that we are so used to in the worlds of laptops, tablets, smartphones and game consoles.
Instead, images are displayed by writing a value to each pixel on the display. 
The display is typically a 2-colour display, such as the so-called 'e-paper' that we 
see on Kindle devices and wrist watches, OLED and and LCD displays.

In this article we describe how to create a C-code in the form of a C-array from any image
for use in embedded system 2-colour displays, where file-size on devices 
still plays a significant role in the business of IoT development, and how you 
can set up an automated tool chain in the BASH command shell to consistently automate this processs. 
The end result is a ready-to-compile C header-file that displays a 32x32 pixel 2-colour icon. 
With a few additional steps. it possible to generate display code for 3-colour embedded displays,
but will limit ourselves to the simpler case here of 2 colours.
Expect to see some interesting BASH techniques here!

# Requirements

You will need to have ImageMagick installed, and the usual gang of Linux utilities,
such as hexdump and the non-sensically-named `xxd` utility. As a general rule, I use icons
exclusively from `Font Awesome` in my front-end development (both web and embedded), since there
is a huge variety of icons on offer and because of the consistent styling among them. The icons
also come in several variants, my preference is the "regular" variant.

# Select your source bitmat

We start with the downloading of the FontAwesome desktop package from https://fontawesome.com/download. 
Unpack it and select your source icon from the svgs directory and move it into your work area.
This file is still the scalable vector graphics format, the first manipulation is to convert it to a bitmap
and to simultaneously resize it. It is useful to leave a blank 1 pixel-wide border around display icons, 
we therefore aim to produce a 30x30 pixel bitmap first and then add the border afterwards to get to our 32x32 pixel bitmap. 


> Note: The intermediate files that are produced are named a, b, c, etc... with appropriate extensions
> to help you keep track of the process.

```bash
$ cd fontawesome-pro-x.xx.x-web/svgs/regular 
$ exclamation-circle.svg workarea/.
$ cd workarea
```

# Create that Bitmap!

A BMP-file not only holds the rasterized image-data in a nice, continuous block of data, 
but in its header it also holds parameters for corectly displaying, e.g. width, height, colour depth, etc. 
It is of course the rasterized image-data that we are after and want convert into C-code.

We use the `convert` utility from ImageMagick to convert the SVG-file to a 30x30 pixel BMP-file.
```bash
$ convert exclamation-circle.svg -resize 30x30 a.bmp
```

Put a 1 pixel border around it to make it 32 x 32 pixels in size.
```bash
$ convert a.bmp -bordercolor white -border 1x1 b.bmp
```

Set the colour depth to 2 colours, so that we have a single bit per pixel in the end:
```bash
$ convert b.bmp -depth 2 c.bmp
```

Set the colour pallete to 2 colours:
```bash
$ convert c.bmp +dither -colors 2 -colorspace gray -contrast-stretch 0 d.bmp
```

Check that we have 2 colours and 1 bit per pixel:

```bash
$ identify d.bmp 
d.bmp BMP 32x32 32x32+0+0 1-bit sRGB 2c 274B 0.000u 0:00.000
```

Also look at some other bitmap file properties by doing a binary dump in hexadecimal:

```bash
$ hexdump -C -v d.bmp | head

00000000  42 4d 12 01 00 00 00 00  00 00 92 00 00 00 7c 00  |BM............|.|
00000010  00 00 20 00 00 00 20 00  00 00 01 00 01 00 00 00  |.. ... .........|
00000020  00 00 80 00 00 00 c3 0e  00 00 c3 0e 00 00 02 00  |................|
00000030  00 00 02 00 00 00 00 00  ff 00 00 ff 00 00 ff 00  |................|
00000040  00 00 00 00 00 ff 42 47  52 73 00 00 00 00 00 00  |......BGRs......|
00000050  00 00 00 00 00 40 00 00  00 00 00 00 00 00 00 00  |.....@..........|
00000060  00 40 00 00 00 00 00 00  00 00 00 00 00 40 00 00  |.@...........@..|
00000070  00 00 00 00 00 00 00 00  00 00 04 00 00 00 00 00  |................|
00000080  00 00 00 00 00 00 00 00  00 00 00 00 00 00 ff ff  |................|
00000090  ff 00 ff ff ff ff ff fe  7f ff ff e0 07 ff ff 80  |................|
```

The 1 at address 0x1C tells us that we are still dealing with a 1-bit, 2-colour depth image file.
We can also confirm that both width (at 0x12) and height (at 0x16) are 32 pixels (0x20).

# Finally getting to the image data

So far, so good, but looking at the file format definition, the beginning of the image's raster-data
is not easy to determine due to all sorts of colour space definitions and arbitrary gaps being allowed for
in the specification. 
So rather than fathoming out the logic for the particular BMP-file that we are using, 
the easiest way to find the beginning of the image-data is to count backwards from the end of the file. 

Since we have 1 bit per pixel, and we have 32 x 32 = 1024 pixels, which amounts to 1024 bits, 
we can safely say that the last 1024 / 8 = 128 bytes of the file is image data. 

The curent bitmap file's size is 274 bytes: 

```bash
$ stat -c%s d.bmp
274
``` 

We therefore need to lopp off the leading 274 - 128 - 146 bytes from the file, so that we end up with the purest, bit-distilled, Highland-quality uncompromised image-data and put the result in file 'e.raster' (strictly-speaking, this is not a Bitmap file any more).

```bash
$ dd if=d.bmp of=e.raster skip=146 iflag=skip_bytes,count_bytes
```

The new raster file should be 128 bytes in size:

```bash
$ stat -c%s e.raster
128
```

Lucky for us, we chose to work with icon files of size 32x32, which fits neatly into the 
display format used by the `xxd`-utility. So when we display file 'e.raster' in binary form (-b) in 4 columns (-c 4) of 8 bits each, we get:

```bash
$ xxd -b -c 4 e.raster

00000000: 11111111 11111111 11111111 11111111  ....
00000004: 11111111 11111110 01111111 11111111  ....
00000008: 11111111 11100000 00000111 11111111  ....
0000000c: 11111111 10000000 00000001 11111111  ....
00000010: 11111110 00000011 11000000 01111111  ....
00000014: 11111100 00011111 11111000 00111111  ...?
00000018: 11111000 01111111 11111110 00011111  ....
0000001c: 11110000 11111111 11111111 00001111  ....
00000020: 11110001 11111110 01111111 10001111  ....
00000024: 11100011 11111100 00111111 11000111  ..?.
00000028: 11100011 11111100 00111111 11000111  ..?.
0000002c: 11000111 11111100 00111111 11100011  ..?.
00000030: 11000111 11111110 01111111 11100011  ....
00000034: 11000111 11111111 11111111 11100011  ....
00000038: 11001111 11111100 00111111 11110011  ..?.
0000003c: 10001111 11111100 00111111 11110001  ..?.
00000040: 10001111 11111100 00111111 11110001  ..?.
00000044: 11001111 11111100 00111111 11110011  ..?.
00000048: 11000111 11111100 00111111 11100011  ..?.
0000004c: 11000111 11111100 00111111 11100011  ..?.
00000050: 11000111 11111100 00111111 11100011  ..?.
00000054: 11100011 11111100 00111111 11000111  ..?.
00000058: 11100011 11111100 00111111 11000111  ..?.
0000005c: 11110001 11111111 11111111 10001111  ....
00000060: 11110000 11111111 11111111 00001111  ....
00000064: 11111000 01111111 11111110 00011111  ....
00000068: 11111100 00011111 11111000 00111111  ...?
0000006c: 11111110 00000011 11000000 01111111  ....
00000070: 11111111 10000000 00000001 11111111  ....
00000074: 11111111 11100000 00000111 11111111  ....
00000078: 11111111 11111110 01111111 11111111  ....
0000007c: 11111111 11111111 11111111 11111111  ....
```

You can make out an upside-down exclamation mark icon if you squint your eyes...
The image is stored upside down for reasons that hark back to the age of the French Revolution and OS/2. 

# Fixing the upside-down problem

On a typical embedded system, the inclination would be to program the display of raster images 
such that they start from the top left corner. This is annoying but we can fix this here by reversing the content 
on a bit-wise basis. Reversing a the byte-level will deliver some interesting resuts! 
If this does not bother you, skip this next step:

On the first line below, we crack the binary file 'e.raster' into a long string of binary 1s and 0s and reverse the string (in one step).
Then we reconstitute the binary file by chunking the binary string up into 8-character long chunks and converting each binary chunk
directly into a hexadecimal string with the printf statement, 
which is then passed to the magic 'xxd' utility that converts the hex string to binary and appends it to the file 'f.raster'. 

```bash
rm -f.raster 2>/dev/null
binstr=$(xxd -b -c 1 e | cut -f 2 -d " " | sed -E 's/(.)/\1 /g' | tr '\n' ' ' | sed -E 's/ //g' | rev )
for ((i=0;i<${#binstr};i+=8)); do 
  binchar=${binstr:$i:8}  
  printf "%02X " $((2#${binchar})) | xxd -r -p >> f.raster
done
```

A quick check reveals that the image is now the correct way around:

```bash
$ xxd -b -c 4 f.raster

00000000: 11111111 11111111 11111111 11111111  ....
00000004: 11111111 11111110 01111111 11111111  ....
00000008: 11111111 11100000 00000111 11111111  ....
0000000c: 11111111 10000000 00000001 11111111  ....
00000010: 11111110 00000011 11000000 01111111  ....
00000014: 11111100 00011111 11111000 00111111  ...?
00000018: 11111000 01111111 11111110 00011111  ....
0000001c: 11110000 11111111 11111111 00001111  ....
00000020: 11110001 11111111 11111111 10001111  ....
00000024: 11100011 11111100 00111111 11000111  ..?.
00000028: 11100011 11111100 00111111 11000111  ..?.
0000002c: 11000111 11111100 00111111 11100011  ..?.
00000030: 11000111 11111100 00111111 11100011  ..?.
00000034: 11000111 11111100 00111111 11100011  ..?.
00000038: 11001111 11111100 00111111 11110011  ..?.
0000003c: 10001111 11111100 00111111 11110001  ..?.
00000040: 10001111 11111100 00111111 11110001  ..?.
00000044: 11001111 11111100 00111111 11110011  ..?.
00000048: 11000111 11111111 11111111 11100011  ....
0000004c: 11000111 11111110 01111111 11100011  ....
00000050: 11000111 11111100 00111111 11100011  ..?.
00000054: 11100011 11111100 00111111 11000111  ..?.
00000058: 11100011 11111100 00111111 11000111  ..?.
0000005c: 11110001 11111110 01111111 10001111  ....
00000060: 11110000 11111111 11111111 00001111  ....
00000064: 11111000 01111111 11111110 00011111  ....
00000068: 11111100 00011111 11111000 00111111  ...?
0000006c: 11111110 00000011 11000000 01111111  ....
00000070: 11111111 10000000 00000001 11111111  ....
00000074: 11111111 11100000 00000111 11111111  ....
00000078: 11111111 11111110 01111111 11111111  ....
0000007c: 11111111 11111111 11111111 11111111  ....
```

Check that this raster file is still 128 bytes in size:

```bash
$ stat -c%s f.raster
128
```

# Generation of the C header-file 

Again, the magic workings of the 'xxd' utility comes into play to generate the C-array
from the binary raster file. You can pipe this output into a C header-file:

```bash
$ xxd -i f.raster >> bitmaps.h
$ cat bitmaps.h

unsigned char f_raster[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xe0, 0x07, 0xff,
  0xff, 0x80, 0x01, 0xff, 0xfe, 0x03, 0xc0, 0x7f, 0xfc, 0x1f, 0xf8, 0x3f,
  0xf8, 0x7f, 0xfe, 0x1f, 0xf0, 0xff, 0xff, 0x0f, 0xf1, 0xff, 0xff, 0x8f,
  0xe3, 0xfc, 0x3f, 0xc7, 0xe3, 0xfc, 0x3f, 0xc7, 0xc7, 0xfc, 0x3f, 0xe3,
  0xc7, 0xfc, 0x3f, 0xe3, 0xc7, 0xfc, 0x3f, 0xe3, 0xcf, 0xfc, 0x3f, 0xf3,
  0x8f, 0xfc, 0x3f, 0xf1, 0x8f, 0xfc, 0x3f, 0xf1, 0xcf, 0xfc, 0x3f, 0xf3,
  0xc7, 0xff, 0xff, 0xe3, 0xc7, 0xfe, 0x7f, 0xe3, 0xc7, 0xfc, 0x3f, 0xe3,
  0xe3, 0xfc, 0x3f, 0xc7, 0xe3, 0xfc, 0x3f, 0xc7, 0xf1, 0xfe, 0x7f, 0x8f,
  0xf0, 0xff, 0xff, 0x0f, 0xf8, 0x7f, 0xfe, 0x1f, 0xfc, 0x1f, 0xf8, 0x3f,
  0xfe, 0x03, 0xc0, 0x7f, 0xff, 0x80, 0x01, 0xff, 0xff, 0xe0, 0x07, 0xff,
  0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff
};
unsigned int f_raster_len = 128;
```

You can see that the name of the raster file is used in the variable name of the C-array.
A useful convention is to retain the original icon name throughout the process
and to append the size attributes to the file name, e.g. the final file name would in 
in this case be exclamation-circle.32x32, to end up with the variable name like this:

```C
unsigned char exclamation-circle_32x32[] = {
  ...
};
```

# References

* https://fontawesome.com/ Font Awesome
* https://imagemagick.org/index.php ImageMagick
* https://en.wikipedia.org/wiki/BMP_file_format  BMP-File format specification