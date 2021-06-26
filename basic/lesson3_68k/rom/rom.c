
extern int _stext;
extern int _estack;
extern int _vram;

typedef struct 
{
  /* Stack pointer */
  void* pStack;
  void* pReset;
  void* fill[62];
} DeviceVectors;

int main();

__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {
        .pStack = (void*) (&_estack),
        .pReset = (void*) (&main)
};

short *vram ;

void put_pixel(unsigned int x, unsigned int y, unsigned short color) {
  vram[320*y+x] = color;
}

// bresenham algorithm to draw a line
void draw_line(int x, int y, int x2, int y2, unsigned short color) 
{
  int longest, shortest, numerator, i;
  int dx1 = (x < x2) ? 1 : -1;
  int dy1 = (y < y2) ? 1 : -1;
  int dx2, dy2;
  
  
  longest = ( x2 > x ) ? x2 - x : x - x2;
  shortest = ( y2 > y ) ? y2 - y : y - y2;

  if (longest < shortest) {
    longest = ( y2 > y ) ? y2 - y : y - y2;
    shortest = ( x2 > x ) ? x2 - x : x - x2;
    dx2 = 0;            
    dy2 = dy1;
  } else {
    dx2 = dx1;
    dy2 = 0;
  }

  numerator = longest/2;
  for (i=0; i<=longest; i++) {
    put_pixel(x,y,color) ;
    if (numerator >= longest-shortest) {
      numerator += shortest ;
      numerator -= longest ;
      x += dx1;
      y += dy1;
    } else {
      numerator += shortest ;
      x += dx2;
      y += dy2;
    }
  }
}

int main() 
{
  int i;
  int w = 320;
  int h = 240;

  unsigned short color = 0;

  vram = (short*)&_vram;

  // clear screen
  for(i=0;i<76800;i++)
    vram[i] = 0;

  // draw colorful lines forever ...
  while(1) {
    for (i=0;i<h;i++)
	draw_line(0,0,w-1,i,color++);

    for(i=w-1;i>=0;i--)
	draw_line(0,0,i,h-1,color++);
    
    for(i=0;i<w;i++)
	draw_line(0,h-1,i,0,color++);

    for(i=0;i<h;i++)
	draw_line(0,h-1,w-1,i,color++);
    
    for(i=h-1;i>=0;i--)
	draw_line(w-1,h-1,0,i,color++);

    for(i=0;i<w;i++)
	draw_line(w-1,h-1,i,0,color++);
    
    for(i=w-1;i>=0;i--)
	draw_line(w-1,0,i,h-1,color++);

    for(i=h-1;i>=0;i--)
	draw_line(w-1,0,0,i,color++);
  }
}

