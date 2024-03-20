# spiral
スパイラル曲線を描画

![image](https://user-images.githubusercontent.com/2605401/218141123-4dd306e1-1bae-4eed-9c0f-b8c3f3340a2e.png)

```
void drawspiral(HDC hdc,int cx,int cy)
{
	const double numRevs=20;
	const double iNumPoints=numRevs*2*(cx+cy);
	cx/=2;
	cy/=2;
	const double np=iNumPoints/numRevs;
	double x=cx*2.0;
	double y=cy;
	for(int i=0;i<iNumPoints;i+=50)
	{
		double fAngle=i*2.0*3.14159265/np;
		double fScale=1.0-i/iNumPoints;
		MoveToEx(hdc,x,y,0);
		x=cx*(1.0+fScale*cos(fAngle));
		y=cy*(1.0+fScale*sin(fAngle));
		LineTo(hdc,x,y);
	}
}
```
