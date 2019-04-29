#using <System.Drawing.dll>

using namespace System;
using namespace System::Drawing;

int main()
{
	Image^ image = Image::FromFile("mochi.jpg");
	image->RotateFlip(RotateFlipType::Rotate90FlipNone);
	image->Save("mochi_rotated.jpg");
	return 0;
}
