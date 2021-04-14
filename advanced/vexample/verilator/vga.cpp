#include "svdpi.h"
#include <signal.h>
#include "Vff_verilator__Dpi.h"

#define NEWVERILATOR 1

#ifdef _WIN32
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

SDL_GameController* gGameController = NULL;
Uint32 * pixels;
SDL_Renderer * renderer =NULL;
SDL_Texture * texture =NULL;

static int rows, cols;
static unsigned int row_sink, col_sink;
//static unsigned int col_hsync, row_vsync;
static unsigned int old_hsync, old_vsync;
static unsigned int pw_hsync, pw_vsync;
static int show_vis;
static int show_stats;

static struct {
    int hpol, vpol;
    unsigned int pw_hsync_hi, pw_hsync_lo;
    unsigned int pw_vsync_hi, pw_vsync_lo;
    unsigned int cols_h, rows_v, cols_hsync, rows_vsync;
    
} stats;

static void init_stats(void)
{
    stats.hpol = -1;
    stats.vpol = -1;
    stats.cols_h = -1;
    stats.rows_v = -1;
    stats.cols_hsync = -1;
    stats.rows_vsync = -1;
}

static void dump_stats(void)
{
    printf("vga: ");
    printf("hpol:%s ", stats.hpol >= 0 ? (stats.hpol > 0 ? "+" : "-") : "unknown");
    printf("vpol:%s ", stats.vpol >= 0 ? (stats.vpol > 0 ? "+" : "-") : "unknown");
    printf("hpw: hi%d lo%d ", stats.pw_hsync_hi, stats.pw_hsync_lo);
    printf("vpw: hi%d lo%d ", stats.pw_vsync_hi, stats.pw_vsync_lo);
    printf("hcols:%d ", stats.cols_h);
    printf("hcols-sync:%d ", stats.cols_hsync);
    printf("vlines:%d ", stats.rows_v);
    printf("vlines-sync:%d ", stats.rows_vsync);
    printf("\n");
}

#if NEWVERILATOR
void dpi_vga_init (const svLogicVecVal* h, const svLogicVecVal* v)
{
    int flags=0;

    cols = h->aval;
    rows = v->aval;
#else
void dpi_vga_init(int h, int v)
{
    int flags;

    cols = h;
    rows = v;
#endif
    show_vis = 0;
    show_stats = 0;

    printf("Initialize display %dx%d\n", cols, rows);

    flags = SDL_INIT_VIDEO | SDL_INIT_JOYSTICK;

    if (SDL_Init(flags)) {
        printf("SDL initialization failed\n");
        return;
    }

    //Check for joysticks
    if( SDL_NumJoysticks() < 1 )
    {
            printf( "Warning: No joysticks connected!\n" );
    }
    else
    {
            //Load joystick
            gGameController = SDL_GameControllerOpen( 0 );
            if( gGameController == NULL )
            {
                printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
            }
    }

    /* NOTE: we still want Ctrl-C to work - undo the SDL redirections*/
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

    SDL_Window * window = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, cols, rows, 0);

    if (!window) {
        printf("Could not open SDL display\n");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    // the texture should match the GPU so it doesn't have to copy
    texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 800, 600);
    pixels = (Uint32 *)calloc(sizeof(Uint32),rows*cols);
    memset(pixels, 255, cols* rows* sizeof(Uint32));

    row_sink = 0;
    col_sink = 0;
//    col_hsync = 0;
//    row_vsync = 0;

    init_stats();
}

int joystick_update() 
{
   SDL_PumpEvents();
}
int joystick_fire() 
{
   int fire = 0;
   const Uint8 *state = SDL_GetKeyboardState(NULL);
   if (state[SDL_SCANCODE_SPACE]) {
    printf("<SPACE> is pressed.\n");
    fire=1;
    }
   if (SDL_GameControllerGetButton(gGameController,SDL_CONTROLLER_BUTTON_X))
     fire = 1;

   return fire;
}
int joystick_start() 
{
   int start= 0;
   const Uint8 *state = SDL_GetKeyboardState(NULL);
   if (state[SDL_SCANCODE_1]) {
    printf("<ONE> is pressed.\n");
    start=1;
    }
   if (SDL_GameControllerGetButton(gGameController,SDL_CONTROLLER_BUTTON_START))
     start= 1;

   return start;
}
int joystick_coin() 
{
   int coin= 0;
   const Uint8 *state = SDL_GetKeyboardState(NULL);
   if (state[SDL_SCANCODE_5]) {
    printf("<FIVE> is pressed.\n");
    coin=1;
    }
   if (SDL_GameControllerGetButton(gGameController,SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
     coin= 1;

   return coin;
}
int joystick_up() 
{
   int button= 0;
   const Uint8 *state = SDL_GetKeyboardState(NULL);
   if (state[SDL_SCANCODE_UP]) {
    printf("<UP> is pressed.\n");
    button=1;
    }
   if (SDL_GameControllerGetButton(gGameController,SDL_CONTROLLER_BUTTON_DPAD_UP))
     button= 1;

   return button;
}
int joystick_down() 
{
   int button= 0;
   const Uint8 *state = SDL_GetKeyboardState(NULL);
   if (state[SDL_SCANCODE_DOWN]) {
    printf("<DOWN> is pressed.\n");
    button=1;
    }
   if (SDL_GameControllerGetButton(gGameController,SDL_CONTROLLER_BUTTON_DPAD_DOWN))
     button= 1;

   return button;
}

int joystick_right() 
{
   int button= 0;
   const Uint8 *state = SDL_GetKeyboardState(NULL);
   if (state[SDL_SCANCODE_RIGHT]) {
    printf("<RIGHT> is pressed.\n");
    button=1;
    }
   if (SDL_GameControllerGetButton(gGameController,SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
     button= 1;

   return button;
}
int joystick_left() 
{
   int button= 0;
   const Uint8 *state = SDL_GetKeyboardState(NULL);
   if (state[SDL_SCANCODE_LEFT]) {
    printf("<LEFT> is pressed.\n");
    button=1;
    }
   if (SDL_GameControllerGetButton(gGameController,SDL_CONTROLLER_BUTTON_DPAD_LEFT))
     button= 1;

   return button;
}

//static int eol;
//static int eof;

#if NEWVERILATOR
void dpi_vga_display(const svLogicVecVal* vsynv, const svLogicVecVal* hsynv, const svLogicVecVal *pixelv)
//void dpi_vga_display(int vsync, int hsync, int pixel)
{
    int vsync, hsync, pixel;
    vsync = vsynv->aval;
    hsync = hsynv->aval;
    pixel= pixelv->aval;

#else
void dpi_vga_display(int vsync, int hsync, int pixel)
{
#endif
    int offset, hedge, vedge;

    if(texture== NULL) {
        printf("Error: display not initialized\n");
        return;
    }



    /* edge detect */
    hedge = 0;
    vedge = 0;

    if (vsync != old_vsync) 
    {
        vedge++;

        if (vsync)
            stats.pw_vsync_lo = pw_vsync;
        else
            stats.pw_vsync_hi = pw_vsync;

        /* record polarity if we have not yet */
        if (stats.vpol < 0 && stats.pw_vsync_lo && stats.pw_vsync_hi) {
            if (stats.pw_vsync_lo > stats.pw_vsync_hi)
                stats.vpol = +1;
            else
                if (stats.pw_vsync_lo < stats.pw_vsync_hi)
                    stats.vpol = 0;
        }

        old_vsync = vsync;
        pw_vsync = 0;
    } else
        pw_vsync++;

    if (hsync != old_hsync) {
        hedge++;

        if (hsync)
            stats.pw_hsync_lo = pw_hsync;
        else
            stats.pw_hsync_hi = pw_hsync;

        /* record polarity if we have not yet */
        if (stats.hpol < 0 && stats.pw_hsync_lo > 0 && stats.pw_hsync_hi > 0) {
            if (stats.pw_hsync_lo > stats.pw_hsync_hi)
                stats.hpol = +1;
            else
                if (stats.pw_hsync_lo < stats.pw_hsync_hi)
                    stats.hpol = 0;
        }

        old_hsync = hsync;
        pw_hsync = 0;
    } else
        pw_hsync++;

    /* end of vblank? */
    if (vedge) {
        if (vsync != stats.vpol) {
            /* end of pulse */
            if (show_vis) printf("vga: visable lines %d\n", row_sink);
            if (0) printf("Frame Complete\n");
            if (show_stats) dump_stats();

#if 1
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_UpdateTexture(texture, NULL, pixels, 800 * sizeof(Uint32));
SDL_Event event;
    if (SDL_PollEvent( & event)) {
        if (event.type == SDL_QUIT) {
            //isquit = true;
        }
    }
#endif

            stats.rows_vsync = row_sink - stats.rows_v + 1;
            row_sink = col_sink = 0;
            return;
        } else {
            stats.rows_v = row_sink;
        }
    }

    /* end of hblank? */
    if (hedge) {
        if (hsync != stats.hpol) {
            /* end of pulse */
            if (show_vis) printf("vga: visable h pixels %d\n", col_sink);
            row_sink++;
            stats.cols_hsync = col_sink - stats.cols_h + 1;
            col_sink = 0;
            return;
        } else {
            stats.cols_h = col_sink;
        }
    }

#if 0
    if (vsync == 0)
    {
        if(eof) {
            eof = 0;
            if (show_vis) printf("vga: visable lines %d\n", row_sink);
            if (0) printf("Frame Complete\n");
            if (show_stats) dump_stats();
            row_vsync = 0;
        }
        row_vsync++;
        row_sink = col_sink = 0;
        eol = 0;
        return;
    } else {
        if (row_vsync) {
            if (show_vis) printf("vga: invisable v lines %d\n", row_vsync);
            row_vsync = 0;
        }
    }

    if (hsync == 0)
    {
        if (eol) {
            if (show_vis) printf("vga: visable h pixels %d\n", col_sink);
            row_sink++;
            col_hsync = 0;
        }
        col_hsync++;
        eol = 0;
        col_sink = 0;
        return;
    } else {
        if (col_hsync) {
            if (show_vis) printf("vga: invisable h pixels %d\n", col_hsync);
            stats.col_hsync = col_hsync;
            col_hsync = 0;
        }
    }
#endif

    if (col_sink >= cols ||
        row_sink >= rows)
        return;

    /* do it */
    offset = (row_sink * cols) + col_sink;

    if (pixel & 0) printf("vga: pixel[%d,%d %d] <- %x\n", row_sink, col_sink, offset, pixel);

    pixels[offset] = pixel|0x000F;

    col_sink++;
 
#if 0
    eol = 1;
    eof = 1;
#endif

}

#ifdef __cplusplus
}
#endif


/*
 * Local Variables:
 * indent-tabs-mode:nil
 * c-basic-offset:4
 * End:
*/

