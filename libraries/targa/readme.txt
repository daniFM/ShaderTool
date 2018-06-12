
Quick feature list:

Simple programming interface - I hate overcomplicated library APIs.

    + Understands all of the sane Targa formats:
        8-bit colormapped
        8-bit grayscale
        16- and 24-bit truecolor BGR
        32-bit truecolor BGRA
    + Reads and writes RLE compressed Targas
    + Reader honors "image descriptor" specification of vertical (top-to-bottom
      or bottom-to-top) and horizontal orientation.
    + Appropriate error-checking - it shouldn't break unless you abuse the API.
    + Handy-dandy image manipulation functions:
        In-place vertical flip.
        In-place horizontal flip.
        Color unmapping - converts colormapped image to truecolor.
        Color desaturation - converts truecolor to grayscale using arbitrary color weights.
        Truecolor bit-depth conversion - i.e. 24 to 16.
        In-place BGR to RGB conversion.
    + Portable.

I have successfully tested this code on the following platforms:

    Win32/i386/MSVC++ 6.0
    Solaris/sun4u/gcc 3.2.1
    FreeBSD/i386/gcc 2.95.4
    Linux/i386/gcc 3.2.2

I haven't had the chance to test it with other Win32 compilers or any older DOS
compilers. If you get the chance to do this, please mail me with your results.


http://dmr.ath.cx/gfx/targa/
