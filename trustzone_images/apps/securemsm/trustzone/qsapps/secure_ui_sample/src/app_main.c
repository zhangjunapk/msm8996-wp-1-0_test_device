/*
@file app_main.c
@brief Secure UI Sample App main entry point.

*/

/*===========================================================================
 Copyright (c) 2013-2015 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE

# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
 07/29/15    ng     Enable GP dialogs on 8996
 02/05/15    rz     Modified according to the secure indicator changes in dialogParams
 08/14/14    rz     Logo is read before the indicator
 01/30/14    rk     Removed fs.h and added qsee_fs.h
 05/26/13	 sn		Initial Version
===========================================================================*/

#include "sselog.h"
#include <comdef.h>
#include "qsee_fs.h"
#include "qsee_sfs.h"
#include <string.h>
#include "qsee_log.h"
#include "qsee_services.h"
#include "qsee_core.h"
#include "SecureUI.h"
#include <stdio.h>
#include "SecureUILib.h"
#include <stringl.h>
#include "qsee_heap.h"
#include "AccessControlHyp.h"
#include "qsee_tui_dialogs.h"

/* commands supported from sample client */
#define SEC_UI_SAMPLE_CMD0_START_SEC_UI        0
#define SEC_UI_SAMPLE_CMD1_SHOW_IMAGE          1
#define SEC_UI_SAMPLE_CMD2_STOP_DISP           2
#define SEC_UI_SAMPLE_CMD3_SHOW_IMAGE_PTR      3
#define SEC_UI_SAMPLE_CMD4_TEST_APP_BUFFER     4

/* GP screens demo commands */
#define SEC_UI_SAMPLE_CMD10_GET_PIN           10
#define SEC_UI_SAMPLE_CMD11_LOGIN             11
#define SEC_UI_SAMPLE_CMD12_MSG_PIN           12
#define SEC_UI_SAMPLE_CMD13_MSG_LOGIN         13
#define SEC_UI_SAMPLE_CMD14_MSG_CLEAN_UP      14

#ifdef ENABLE_QSEE_LOG_MSG_DEBUG
#undef ENABLE_QSEE_LOG_MSG_DEBUG
#define ENABLE_QSEE_LOG_MSG_DEBUG 1
#endif

#define BYTES_PER_PIXEL                        4
#define MAX_FILENAME_LEN                   (256)
#define RED_PIXEL                     0xff0000ff
#define GREEN_PIXEL                   0xff00ff00
#define DOT_SIZE                              10
#define NO_TIMEOUT                          (-1)
#define DEFAULT_TIMEOUT               NO_TIMEOUT
#define TOP_EXIT_BAR                         100

// screen and panel sizes for FLUID and LIQUID
#define FLUID_PANEL_8974_W 760
#define FLUID_PANEL_8974_H 1424
#define FLUID_SCREEN_8974_W 720
#define FLUID_SCREEN_8974_H 1280

#define LIQUID_PANEL_8974_W 1920
#define LIQUID_PANEL_8974_H 1080
#define LIQUID_SCREEN_8974_W 1920
#define LIQUID_SCREEN_8974_H 1080

#define FLUID_PANEL_8084_W 1080
#define FLUID_PANEL_8084_H 2085
#define FLUID_SCREEN_8084_W 1080
#define FLUID_SCREEN_8084_H 1920

#define LIQUID_PANEL_8084_W 2560
#define LIQUID_PANEL_8084_H 1440
#define LIQUID_SCREEN_8084_W 2560
#define LIQUID_SCREEN_8084_H 1440

#define FLUID_PANEL_8994_W 1600
#define FLUID_PANEL_8994_H 2704
#define FLUID_SCREEN_8994_W 1600
#define FLUID_SCREEN_8994_H 2600
#define FLUID_INIT_SCREEN_8994_SZ 0x1040000

#define LIQUID_PANEL_8994_W 3840
#define LIQUID_PANEL_8994_H 2160
#define LIQUID_SCREEN_8994_W 3840
#define LIQUID_SCREEN_8994_H 2160

#define FLUID_PANEL_8996_W 1600
#define FLUID_PANEL_8996_H 2704
#define FLUID_SCREEN_8996_W 1600
#define FLUID_SCREEN_8996_H 2560
#define FLUID_INIT_SCREEN_8996_SZ 0xFA0000

#define MAX_INPUT_LEN_BYTES 500
#define MAX_INPUT_LEN       200
#define MIN_INPUT_LEN         0
#define NUMBER_MSG            4
#define MAX_MSG_LEN         300
#define MAX_UPDATE_EVENTS    40
#define MAX_BUFFERS           5

#define PIN_TITLE "ENTER YOUR PIN"
#define LOGIN_TITLE "SECURE LOGIN"
#define MSG_TITLE "SECURE MESSAGE"
#define DESC_TITLE "Test Secure UI®"
#define MSG_RIGHT_BTN_LABEL "ok"
#define MSG_LEFT_BTN_LABEL "cancel"
#define MSG_MIDDLE_BTN_LABEL ""
#define PASSWORD_LABEL "PASSWORD"
#define USERNAME_LABEL "USERNAME"
#define DEFAULT_USER "sample user"
#define PIN_LABEL ""


//#define SFS 1 // set this flag to read the secure indicator image from SFS
//#define PROVISION 1 // set this flag to provision the secure indicator image into SFS


uint32_t dispH    = 0;
uint32_t dispW    = 0;
uint32_t dispS    = 0;
uint32_t pixelW   = 0;
uint32_t rotation   = 0;
uint8_t *g_screen = NULL;
uint8_t *g_screen_last = NULL;
uint8 red_dot[DOT_SIZE*BYTES_PER_PIXEL];
uint8 green_dot[DOT_SIZE*BYTES_PER_PIXEL];

struct touch_event {
  uint32_t x;
  uint32_t y;
  uint8_t *dot;
};

struct event_queue {
  uint8_t *buffer;
  struct touch_event events[MAX_UPDATE_EVENTS];
};

struct event_queue queue[MAX_BUFFERS] = {0};
char sfs_sec_ind_path[] = "/data/misc/secure_ui/secure_images/secure_logo.png";
char fs_sec_ind_path[] = "/data/local/tmp/sec_ind.png";
char fs_logo_path[] = "/data/local/tmp/logo.png";
uint32_t sec_ind_size = 0;
uint32_t logo_size = 0;

qsee_tui_dialog_ret_val_t status = TUI_SUCCESS;
uint8_t* sec_ind_buffer           = NULL;
uint8_t* logo_buffer           = NULL;
uint8_t received_pin[MAX_INPUT_LEN_BYTES];
uint32_t received_pin_len      = 0;
uint8_t received_username[MAX_INPUT_LEN_BYTES];
uint32_t received_username_len = 0;
uint8_t received_password[MAX_INPUT_LEN_BYTES];
uint32_t received_password_len = 0;

void copy_dot(uint8_t * const buffer, struct touch_event * ev) {
  size_t y = 0;
  size_t dot_width = 0;
  size_t buffer_size = dispS*dispH*pixelW;
  if (dispW - ev->x > DOT_SIZE) {
    dot_width = DOT_SIZE;
  } else {
    dot_width = dispW - ev->x;
  }
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "%s: (%u,%u) onto buffer 0x%08X", __func__, ev->x, ev->y, buffer);
  for(y = ev->y; (y < ev->y + DOT_SIZE) && (y < dispH); y++) {
    memscpy(buffer + (y*dispS + ev->x)*pixelW, buffer_size - (y*dispS + ev->x)*pixelW, ev->dot, dot_width*BYTES_PER_PIXEL);
  }
}

sec_touch_cmd_t draw_dot(sec_touch_err_t err, struct tsFingerData *fingers, int32_t *timeout)
{
  int32_t retval = -1;
  size_t i = 0;
  size_t j = 0;
  size_t k = 0;
  size_t current = 0;
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "%s: err=  %d", __func__, err);

  if(SEC_TOUCH_ERR_STARTED == err){
    *timeout = DEFAULT_TIMEOUT;
    return SEC_TOUCH_CMD_CONTINUE;
  }

  if(SEC_TOUCH_ERR_STOPPED == err)
    return SEC_TOUCH_CMD_COMPLETED;
  if(SEC_TOUCH_ERR_DATA != err)
    return SEC_TOUCH_CMD_CANCELLED;

  // make sure current screen is in the queue
  for(i=0; i<MAX_BUFFERS; i++) {
    if (queue[i].buffer == NULL) {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "%s: New buffer: 0x%08X [%u]", __func__, g_screen, i);
      queue[i].buffer = g_screen;
      current = i;
      break;
    }
    if (queue[i].buffer == g_screen) {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "%s: Buffer 0x%08X already in queue [%u]", __func__, g_screen, i);
      current = i;
      break;
    }
  }
  if (i == MAX_BUFFERS) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "%s: Too many buffers!", __func__);
    return SEC_TOUCH_CMD_CANCELLED;
  }

  for (j = 0; j < MAX_FINGER_NUM; j++) {
    if (fingers->finger[j].event != TLAPI_TOUCH_EVENT_NONE) {
      struct touch_event ev = {0};
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Position: (%u, %u)", fingers->finger[j].x, fingers->finger[j].y);
      if (fingers->finger[j].y < TOP_EXIT_BAR) {
        return SEC_TOUCH_CMD_COMPLETED;
      }
      ev.x = fingers->finger[j].x;
      ev.y = fingers->finger[j].y;
      if (fingers->finger[j].event & TLAPI_TOUCH_EVENT_UP) {
        ev.dot = green_dot;
      } else {
        ev.dot = red_dot;
      }
      // add it to all buffers
      for (i = 0; i < MAX_BUFFERS; i++) {

        if (queue[i].buffer == NULL) break; // done
        for (k = 0; k < MAX_UPDATE_EVENTS; k++) {
          if (queue[i].events[k].dot == NULL) {
            queue[i].events[k] = ev;
            break;
          }
        }
      }
    }
  }

  // draw queue for current buffer
  for (k = 0; k < MAX_UPDATE_EVENTS; k++) {
    if (queue[current].events[k].dot != NULL) {
      copy_dot(queue[current].buffer,&queue[current].events[k]);
      queue[current].events[k].dot = NULL;
    } else {
      break;
    }
  }

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Succeeded drawing dot in secure buffer");
  g_screen_last = g_screen;
  retval = sec_ui_show_buf(FALSE, &g_screen);
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "sec_ui_show_buf returned %d", retval);

  if(retval < 0) {
    return SEC_TOUCH_CMD_CANCELLED;
  }
  // make sure new screen is in the queue
  for(i=0; i<MAX_BUFFERS; i++) {
    if (queue[i].buffer == NULL) {
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "%s: New buffer: 0x%08X [%u]", __func__, g_screen, i);
      queue[i].buffer = g_screen;
      memscpy(g_screen, dispH*dispS*pixelW, g_screen_last, dispH*dispS*pixelW);
      break;
    }
    if (queue[i].buffer == g_screen) break; // there already, nothing to do
  }
  if (i == MAX_BUFFERS) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "%s: Too many buffers!", __func__);
    return SEC_TOUCH_CMD_CANCELLED;
  }

  *timeout = DEFAULT_TIMEOUT;
  return SEC_TOUCH_CMD_CONTINUE;
}

void provision(const char * fs_path, const char* sfs_path){
	int l_fd, sfs_fd;
	uint32_t size_read, i = 0;
	char temp_copy_buf[1024];

	QSEE_LOG(QSEE_LOG_MSG_DEBUG, "trying to open the image = %s", fs_path);
	l_fd = open(fs_path, O_RDWR);
	if(l_fd < 0){
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "failed to open the image = %s", fs_path);
		return;
	}

	qsee_sfs_rm(sfs_path);
	sfs_fd = qsee_sfs_open( sfs_path, O_RDWR | O_CREAT | O_TRUNC );
	if(sfs_fd <= 0){
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "sfs open failed for %s, returned = %d", sfs_path, sfs_fd);
		close(l_fd);
		return;
	}

	/*copy the image from fs to sfs*/
	do {
		size_read = read(l_fd, temp_copy_buf, sizeof(temp_copy_buf));
		qsee_sfs_write( sfs_fd, (const char*)temp_copy_buf, size_read );
		i+=size_read;
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "copying... %d", i);
	} while (size_read > 0);
	QSEE_LOG(QSEE_LOG_MSG_DEBUG, "done copying");
	close(l_fd);
	qsee_sfs_close(sfs_fd);

	QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Done provisioning image = %s", fs_path);
}

void tz_app_init(void) {
	int l_fd, bytes, i ,res;
	fs_stat logo_stat;

	for(i=0;i<DOT_SIZE;i++){
		((uint32 *)red_dot)[i] = RED_PIXEL;
		((uint32 *)green_dot)[i] = GREEN_PIXEL;
	}

	/* logo */
	res = lstat(fs_logo_path,&logo_stat);
	if(res < 0){
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "failed lstat for the logo");
		return;
	}

	logo_size = logo_stat.st_size;

	logo_buffer = (uint8_t*)qsee_malloc(logo_size);
	if(NULL == logo_buffer){
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "failed qsee_malloc the logo buffer");
		return;
	}

	l_fd = open(fs_logo_path, O_RDONLY);
	if(l_fd < 0){
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "failed reading logo image path");
		return;
	}

	bytes = read(l_fd,logo_buffer,logo_size);
	QSEE_LOG(QSEE_LOG_MSG_DEBUG, "read logo image, bytes =%d", bytes);
	close(l_fd);


#ifdef PROVISION

	provision(fs_sec_ind_path, sfs_sec_ind_path);

#endif

#ifdef SFS

	l_fd = qsee_sfs_open(sfs_sec_ind_path, O_RDWR);
	if(l_fd < 0){
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "failed reading image path");
		return;
	}

	res = qsee_sfs_getSize(l_fd, &sec_ind_size);
	if(0 != res){
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "qsee_sfs_getSize failed");
		return;
	}

	sec_ind_buffer = (uint8_t*)qsee_malloc(sec_ind_size);
	if(NULL == sec_ind_buffer){
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "failed qsee_malloc the secure indicator buffer");
		return;
	}

	bytes = qsee_sfs_read(l_fd,(char*)sec_ind_buffer,sec_ind_size);
	QSEE_LOG(QSEE_LOG_MSG_DEBUG, "read image, bytes =%d", bytes);
	qsee_sfs_close(l_fd);

#else

	/* secure indicator */
	fs_stat sec_ind_stat;
	res = lstat(fs_sec_ind_path,&sec_ind_stat);
	if(res < 0){
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "failed lstat for the indicator. Trying to display the secure indicator instead");
		//qsee_tui_init();
		return;
	}

	sec_ind_size = sec_ind_stat.st_size;

	sec_ind_buffer = (uint8_t*)qsee_malloc(sec_ind_size);
	if(NULL == sec_ind_buffer){
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "failed qsee_malloc the secure indicator buffer");
		return;
	}

	l_fd = open(fs_sec_ind_path, O_RDONLY);
	if(l_fd < 0){
		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "failed reading the secure indicator image path");
		return;
	}

	bytes = read(l_fd,sec_ind_buffer,sec_ind_size);
	QSEE_LOG(QSEE_LOG_MSG_DEBUG, "read secure indicator image, bytes =%d", bytes);
	close(l_fd);

#endif

	qsee_tui_init();
}

struct send_cmd{
  uint32_t cmd_id;
  uint32_t height;
  uint32_t width;
  uint32_t x;
  uint32_t y;
  uint32_t timeout;
  char img_path[MAX_FILENAME_LEN];
};

struct send_cmd_rsp{
  int32_t status;
};

static int32_t test_app_buffer_alloc(uint32_t buf_len)
{
  int32_t ret = 0;
  boolean prot = FALSE;
  uint8_t *buf;

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, " START: test App buffer: alloc on length=%u", buf_len);
  ret = sec_ui_alloc_app_buffer(buf_len, &buf);
  if (ret < 0) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, " failed to allocate app buffer. Returned: %d", ret);
    return 0;
  }
  prot = qsee_is_s_tag_area(AC_VM_CP_APP, (uint32_t)buf, (uint32_t)buf + buf_len);
  if (!prot) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, " app buffer not correctly protected.");
    return 0;
  }
  ret = sec_ui_free_app_buffer();
  if (ret < 0) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, " failed to free the app buffer. Returned: %d", ret);
    return 0;
  }

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, " End: test App buffer SUCCESS");
  return 1;
}

static int32_t test_app_buffer_free_noalloc(void)
{
  int32_t ret = 0;

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "START: test App buffer: free");
  ret = sec_ui_free_app_buffer();
  if (ret == 0) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "sec_ui_free_app_buffer should fail. No previous allocations. Returned: %d", ret);
    return 0;
  }

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "End: test App buffer SUCCESS");
  return 1;
}

static int32_t test_app_buffer_multi_alloc(void)
{
  int32_t ret = 0;
  boolean prot = FALSE;
  uint8_t *buf;
  uint32_t buf_len = 0x10000;

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "START: test App buffer: multi alloc");
  ret = sec_ui_alloc_app_buffer(buf_len, &buf);
  if (ret < 0) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "failed to allocate app buffer. Returned: %d", ret);
    return 0;
  }
  ret = sec_ui_alloc_app_buffer(buf_len, &buf);
  if (ret == 0) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "sec_ui_alloc_app_buffer should fail. Buffer already allocated.");
    return 0;
  }
  prot = qsee_is_s_tag_area(AC_VM_CP_APP, (uint32_t)buf, (uint32_t)buf + buf_len);
  if (!prot) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "app buffer not correctly protected.");
    return 0;
  }
  ret = sec_ui_free_app_buffer();
  if (ret < 0) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "failed to free the app buffer. Returned: %d", ret);
    return 0;
  }

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "End: test App buffer SUCCESS");
  return 1;
}

static int32_t test_app_buffer_alloc_multi_length(void)
{
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "START: test App buffer: alloc multi length");
  if (!test_app_buffer_alloc(0x1))
    return 0;
  if (!test_app_buffer_alloc(0x1000000))
    return 0;
  if (!test_app_buffer_alloc(0x1234567))
    return 0;
  if (!test_app_buffer_alloc(0x2000000))
    return 0;

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "End: test App buffer SUCCESS");
  return 1;
}

static int32_t test_app_buffer_use_app_buffer(void)
{
  int32_t ret = 1;
  boolean prot = FALSE;
  uint8_t *buf = NULL;
  uint32_t buf_len = 0x1000000;
  uint8_t mem_tag_byte = 0xFA;
  int i;

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "START: test App buffer: use buffer");
  
  do {
    if (sec_ui_alloc_app_buffer(buf_len, &buf) < 0) {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "failed to allocate app buffer. Returned: %d", ret);
      return 0;
    }

    memset((void *)buf, mem_tag_byte, buf_len);

    prot = qsee_is_s_tag_area(AC_VM_CP_APP, (uint32_t)buf, (uint32_t)buf + buf_len);
    if (!prot) {
      QSEE_LOG(QSEE_LOG_MSG_ERROR, "app buffer not correctly protected.");
      ret = 0;
      break;
    }

    for (i = 0; i < buf_len; ++i) {
      if (buf[i] != mem_tag_byte) {
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "Wrong content read in the app buffer");
        ret = 0;
        break;
      }
    }
  } while(0);

  if (sec_ui_free_app_buffer() < 0) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "failed to free the app buffer. Returned: %d", ret);
    return 0;
  }

  if (ret == 1)
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "End: test App buffer SUCCESS");
  return ret;

}

int32_t test_app_buffer(void)
{
  int32_t ret = 0;
  if (!test_app_buffer_alloc_multi_length()) {
      ret += -1;
  }
  if (!test_app_buffer_free_noalloc()) {
      ret += -1;
  }
  if (!test_app_buffer_multi_alloc()) {
      ret += -1;
  }
  if (!test_app_buffer_use_app_buffer()) {
      ret += -1;
  }
  return ret;
}

int32_t alloc_init_screen(uint8_t **buf, uint32_t buf_len)
{
  int32_t retval = 0;
  uint8_t *tbuf;

  retval = sec_ui_alloc_app_buffer(buf_len, buf);
  if (retval < 0) {
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "failed to allocate app buffer %d", retval);
    return retval;
  }
  tbuf = *buf;
  if (!qsee_is_s_tag_area(AC_VM_CP_APP, (uint32_t)tbuf, (uint32_t)tbuf + buf_len)) {
    QSEE_LOG(QSEE_LOG_MSG_DEBUG, "buffer not tagged properly");
    return -1;
  }

  memset((void *)tbuf, 0xAB, buf_len);

  return retval;

}

void start_disp_fullscreen(struct send_cmd *cmd_ptr,
                                 struct send_cmd_rsp *rsp_ptr)
{
  int32_t retval = -1;
  uint8_t *initScreen = NULL;
  uint32_t initScreenLen = 0x0;

  retval = sec_ui_get_disp_properties(&dispH, &dispW);
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "sec_ui_get_disp_properties returned  %d", retval);

  if(retval < 0){
    rsp_ptr->status = retval;
    return;
  }
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Display size: %u x %u", dispW, dispH);
  if (dispW == LIQUID_PANEL_8974_W) {
    secUiSetPanelSize(LIQUID_PANEL_8974_W, LIQUID_PANEL_8974_H);
  } else if (dispW == FLUID_PANEL_8974_W) {
    secUiSetPanelSize(FLUID_PANEL_8974_W, FLUID_PANEL_8974_H);
  } else if (dispW == LIQUID_PANEL_8084_W) {
    secUiSetPanelSize(LIQUID_PANEL_8084_W, LIQUID_PANEL_8084_H);
  } else if (dispW == FLUID_PANEL_8084_W) {
    secUiSetPanelSize(FLUID_PANEL_8084_W, FLUID_PANEL_8084_H);
  } else if (dispW == LIQUID_PANEL_8994_W) {
    secUiSetPanelSize(LIQUID_PANEL_8994_W, LIQUID_PANEL_8994_H);
  } else if (dispW == FLUID_SCREEN_8994_W && dispH == FLUID_SCREEN_8994_H) {
    secUiSetPanelSize(FLUID_PANEL_8994_W, FLUID_PANEL_8994_H);
    initScreenLen = FLUID_INIT_SCREEN_8994_SZ;
  } else if (dispW == FLUID_SCREEN_8996_W && dispH == FLUID_SCREEN_8996_H) {
	  secUiSetPanelSize(FLUID_PANEL_8996_W, FLUID_PANEL_8996_H);
	  initScreenLen = FLUID_INIT_SCREEN_8996_SZ;
  }
  else {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "No matching panel for width: %u", dispW);
  }

  if (initScreenLen > 0) {
    retval = alloc_init_screen(&initScreen, initScreenLen);
    if(retval < 0){
      rsp_ptr->status = retval;
      return;
    }
  }

  retval = sec_ui_start_disp_fullscreen(HAL_PIXEL_FORMAT_RGBA_8888, initScreen, initScreenLen, 
                                        &g_screen, &dispS, &pixelW, &rotation);
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "sec_ui_start_disp_fullscreen returned  %d", retval);
  if(retval < 0){
    rsp_ptr->status = retval;
    return;
  }

  if(pixelW != BYTES_PER_PIXEL){
	  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "unsupported pixel width %d", pixelW);
	  rsp_ptr->status = -1;
	  return;
  }
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Detected rotation: %d", rotation);

}

void show_image(struct send_cmd     *cmd_ptr,
                struct send_cmd_rsp *rsp_ptr)
{
  int32_t retval = -1;
  int l_fd;
  uint32_t row, h, w;
  struct input_to_copy in;
  QSEE_LOG(QSEE_LOG_MSG_ERROR, "%s+", __func__);

  l_fd = open(cmd_ptr->img_path, O_RDONLY);
  if (l_fd < 0) {
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "Failed to open file %s", cmd_ptr->img_path);
    rsp_ptr->status = l_fd;
    return;
  }

  do {

    in.type = SEC_UI_FD_FS;
    in.input.u32Fd = l_fd;

    h = cmd_ptr->height;
    w = cmd_ptr->width;
    for (row = cmd_ptr->y; row < h + cmd_ptr->y; row++) {
      retval = sec_ui_copy_to_buffer(in, cmd_ptr->x,row, w*BYTES_PER_PIXEL);
      if (retval < 0) {
        rsp_ptr->status = retval;
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "copy to buffer failed; received  %d", retval);
        break;
      }
    }
    if (retval >= 0) {
      retval = sec_ui_show_buf(TRUE, &g_screen);
      if (retval < 0) {
        rsp_ptr->status = retval;
        QSEE_LOG(QSEE_LOG_MSG_ERROR, "show buffer failed; received  %d", retval);
      }
    }
  } while (0);

  if (l_fd >= 0)
    close(l_fd);
}

void show_image_ptr(struct send_cmd     *cmd_ptr,
                    struct send_cmd_rsp *rsp_ptr)
{
  boolean protected = FALSE;
  uint64_t long_res;

  QSEE_LOG(QSEE_LOG_MSG_ERROR, "%s+", __func__);
  
  long_res = (uint64_t)dispH*dispS;
  if(long_res > UINT32_MAX){
    rsp_ptr->status = -1;
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "integer overflow in display properties calculation");
    return;
  }
  
  long_res *= BYTES_PER_PIXEL;
  if(long_res > UINT32_MAX){
    rsp_ptr->status = -1;
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "integer overflow in display properties calculation");
    return;
  }
  
  memset (g_screen, 0, long_res);
  
  long_res += (uint32_t)g_screen;
    if(long_res > UINT32_MAX){
    rsp_ptr->status = -1;
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "integer overflow in display properties calculation");
    return;
  }
  
  protected = qsee_is_s_tag_area(AC_VM_CP_SECDISP, (uint32_t)g_screen, (uint32_t)long_res);
  if (!protected) {
    rsp_ptr->status = -1;
    QSEE_LOG(QSEE_LOG_MSG_ERROR, "Buffer not protected");
    return;
  }
  
  show_image(cmd_ptr, rsp_ptr);  
  
}

static int32_t start_pin_dialog(){
	  qsee_tui_dialog_params_t pin_params = {0};

	  pin_params.dialogType = TUI_DIALOG_PIN;

	  pin_params.dialogCommonParams.title.pu8Buffer = (uint8_t*)PIN_TITLE;
	  pin_params.dialogCommonParams.title.u32Len = strlen(PIN_TITLE);

	  pin_params.dialogCommonParams.description.pu8Buffer = (uint8_t*)DESC_TITLE;
	  pin_params.dialogCommonParams.description.u32Len = strlen(DESC_TITLE);

	  if (sec_ind_buffer != NULL) {
	      // display local indicator
	      pin_params.dialogCommonParams.secureIndicatorParams.bDisplayGlobalSecureIndicator = FALSE;
	      pin_params.dialogCommonParams.secureIndicatorParams.secureIndicator.pu8Buffer = sec_ind_buffer;
	      pin_params.dialogCommonParams.secureIndicatorParams.secureIndicator.u32Len = sec_ind_size;
	  } else {
	      // display global secure indicator
	      pin_params.dialogCommonParams.secureIndicatorParams.bDisplayGlobalSecureIndicator = TRUE;
	  }

	  pin_params.dialogCommonParams.logo.pu8Buffer = logo_buffer;
	  pin_params.dialogCommonParams.logo.u32Len = logo_size;

	  pin_params.dialogCommonParams.n32TimeOut = DEFAULT_TIMEOUT;

	  pin_params.pinDialogParams.inpMode = DISP_MODE_VIS_THEN_HID;

	  pin_params.pinDialogParams.pin.u32MaxLen = MAX_INPUT_LEN;
	  pin_params.pinDialogParams.pin.u32MinLen = MIN_INPUT_LEN;
	  pin_params.pinDialogParams.pin.inpValue.pu8Buffer = received_pin;
	  pin_params.pinDialogParams.pin.inpValue.u32Len = MAX_INPUT_LEN_BYTES;
	  pin_params.pinDialogParams.pin.pu32InpValueLen = &received_pin_len;
	  pin_params.pinDialogParams.pin.defaultValue.pu8Buffer = received_pin;
	  pin_params.pinDialogParams.pin.defaultValue.u32Len = received_pin_len;

	  pin_params.pinDialogParams.pin.label.pu8Buffer = (uint8_t*)PIN_LABEL;
	  pin_params.pinDialogParams.pin.label.u32Len = strlen(PIN_LABEL);

	  pin_params.pinDialogParams.keyPadMode = TUI_KEYPAD_RANDOMIZED;
	  pin_params.pinDialogParams.bHideInputBox = 0;
	  return qsee_tui_dialog(&pin_params,&status);
}

static int32_t start_login_dialog(){
	  qsee_tui_dialog_params_t login_params = {0};

	  login_params.dialogType = TUI_DIALOG_PASSWORD;

	  login_params.dialogCommonParams.title.pu8Buffer = (uint8_t*)LOGIN_TITLE;
	  login_params.dialogCommonParams.title.u32Len = strlen(LOGIN_TITLE);

	  login_params.dialogCommonParams.description.pu8Buffer = (uint8_t*)DESC_TITLE;
	  login_params.dialogCommonParams.description.u32Len = strlen(DESC_TITLE);

	  if (sec_ind_buffer != NULL) {
	      // display local indicator
	      login_params.dialogCommonParams.secureIndicatorParams.bDisplayGlobalSecureIndicator = FALSE;
	      login_params.dialogCommonParams.secureIndicatorParams.secureIndicator.pu8Buffer = sec_ind_buffer;
	      login_params.dialogCommonParams.secureIndicatorParams.secureIndicator.u32Len = sec_ind_size;
	  } else {
	      // display global secure indicator
	      login_params.dialogCommonParams.secureIndicatorParams.bDisplayGlobalSecureIndicator = TRUE;
	  }

	  login_params.dialogCommonParams.logo.pu8Buffer = logo_buffer;
	  login_params.dialogCommonParams.logo.u32Len = logo_size;

	  login_params.dialogCommonParams.n32TimeOut = DEFAULT_TIMEOUT;

	  login_params.pswdDialogParams.inpMode = DISP_MODE_VIS_THEN_HID;
	  login_params.pswdDialogParams.bUserNameInpShow = 1;
	  login_params.pswdDialogParams.bPasswordInpShow = 1;

	  login_params.pswdDialogParams.username.u32MaxLen = MAX_INPUT_LEN;
	  login_params.pswdDialogParams.username.u32MinLen = MIN_INPUT_LEN;
	  login_params.pswdDialogParams.username.inpValue.pu8Buffer = received_username;
	  login_params.pswdDialogParams.username.inpValue.u32Len = MAX_INPUT_LEN_BYTES;
	  login_params.pswdDialogParams.username.pu32InpValueLen = &received_username_len;
	  login_params.pswdDialogParams.username.defaultValue.pu8Buffer = (uint8_t*)DEFAULT_USER;
	  login_params.pswdDialogParams.username.defaultValue.u32Len = strlen(DEFAULT_USER);
	  login_params.pswdDialogParams.username.label.pu8Buffer = (uint8_t*)USERNAME_LABEL;
	  login_params.pswdDialogParams.username.label.u32Len = strlen(USERNAME_LABEL);

	  login_params.pswdDialogParams.password.u32MaxLen = MAX_INPUT_LEN;
	  login_params.pswdDialogParams.password.u32MinLen = MIN_INPUT_LEN;
	  login_params.pswdDialogParams.password.inpValue.pu8Buffer = received_password;
	  login_params.pswdDialogParams.password.inpValue.u32Len = MAX_INPUT_LEN_BYTES;
	  login_params.pswdDialogParams.password.pu32InpValueLen = &received_password_len;
	  login_params.pswdDialogParams.password.defaultValue.pu8Buffer = received_password;
	  login_params.pswdDialogParams.password.defaultValue.u32Len = received_password_len;
	  login_params.pswdDialogParams.password.label.pu8Buffer = (uint8_t*)PASSWORD_LABEL;
	  login_params.pswdDialogParams.password.label.u32Len = strlen(PASSWORD_LABEL);

	  return qsee_tui_dialog(&login_params,&status);
}

static int32_t start_msg_dialog(uint8* msg, uint32_t msg_len){
	  qsee_tui_dialog_params_t msg_params = {0};

	  if(NULL == msg){
		  return TUI_ILLEGAL_INPUT;
	  }

	  msg_params.dialogType = TUI_DIALOG_MESSAGE;

	  msg_params.dialogCommonParams.title.pu8Buffer = (uint8_t*)MSG_TITLE;
	  msg_params.dialogCommonParams.title.u32Len = strlen(MSG_TITLE);

	  msg_params.dialogCommonParams.description.pu8Buffer = (uint8_t*)DESC_TITLE;
	  msg_params.dialogCommonParams.description.u32Len = strlen(DESC_TITLE);

	  if (sec_ind_buffer != NULL) {
	      // display local indicator
	      msg_params.dialogCommonParams.secureIndicatorParams.bDisplayGlobalSecureIndicator = FALSE;
	      msg_params.dialogCommonParams.secureIndicatorParams.secureIndicator.pu8Buffer = sec_ind_buffer;
	      msg_params.dialogCommonParams.secureIndicatorParams.secureIndicator.u32Len = sec_ind_size;
	  } else {
	      // display global secure indicator
	      msg_params.dialogCommonParams.secureIndicatorParams.bDisplayGlobalSecureIndicator = TRUE;
	  }

	  msg_params.dialogCommonParams.logo.pu8Buffer = logo_buffer;
	  msg_params.dialogCommonParams.logo.u32Len = logo_size;

	  msg_params.dialogCommonParams.n32TimeOut = DEFAULT_TIMEOUT;

	  msg_params.msgDialogParams.rightBtnParams.btnLabel.pu8Buffer = (uint8_t*)MSG_RIGHT_BTN_LABEL;
	  msg_params.msgDialogParams.rightBtnParams.btnLabel.u32Len = strlen(MSG_RIGHT_BTN_LABEL);
	  msg_params.msgDialogParams.rightBtnParams.bShowBtn = 1;
	  msg_params.msgDialogParams.rightBtnParams.bDisableBtn = 0;

	  msg_params.msgDialogParams.leftBtnParams.btnLabel.pu8Buffer = (uint8_t*)MSG_LEFT_BTN_LABEL;
	  msg_params.msgDialogParams.leftBtnParams.btnLabel.u32Len = strlen(MSG_LEFT_BTN_LABEL);
	  msg_params.msgDialogParams.leftBtnParams.bShowBtn = 1;
	  msg_params.msgDialogParams.leftBtnParams.bDisableBtn = 0;

	  msg_params.msgDialogParams.middleBtnParams.bShowBtn = 0;
	  msg_params.msgDialogParams.middleBtnParams.btnLabel.pu8Buffer = (uint8_t*)MSG_MIDDLE_BTN_LABEL;
	  msg_params.msgDialogParams.middleBtnParams.btnLabel.u32Len = strlen(MSG_MIDDLE_BTN_LABEL);
	  msg_params.msgDialogParams.middleBtnParams.bDisableBtn = 0;

	  msg_params.msgDialogParams.msg.pu8Buffer = msg;
	  msg_params.msgDialogParams.msg.u32Len = msg_len;

	  return qsee_tui_dialog(&msg_params,&status);
}

void tz_app_cmd_handler(void* cmd, uint32_t cmdlen,
                        void* rsp, uint32_t rsplen)
{
  struct send_cmd *cmd_ptr = (struct send_cmd *)cmd;
  struct send_cmd_rsp *rsp_ptr = (struct send_cmd_rsp *)rsp;
  int32_t retval = -1;
  uint8_t msg[MAX_MSG_LEN];
  char* login_user = "Your username is: ";
  char* login_pass = " Your password is: ";
  char* pin = "Your pin is: ";
  uint32_t len;

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "TZ App cmd handler @ 0x%08X", tz_app_cmd_handler);

  retval = secUiProcessCmd(cmd,cmdlen,rsp,rsplen);
  if (retval > 0)
  {
    return;
  }

  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "status = %d", status);

  if ( NULL == cmd || NULL == rsp) {
	QSEE_LOG(QSEE_LOG_MSG_ERROR, "cmd handler received null cmd/rsp buffers");
    return;
  }

  if ((cmdlen < sizeof(struct send_cmd)) || (rsplen < sizeof(struct send_cmd_rsp))) {
	QSEE_LOG(QSEE_LOG_MSG_ERROR, "cmd handler received too short cmd/rsp buffers %d vs %d, %d vs %d",cmdlen, sizeof(struct send_cmd),rsplen ,sizeof(struct send_cmd_rsp));
    return;
  }

  if (retval < 0) {
	rsp_ptr->status = retval;
	return;
  }
  
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "cmd_id = %d", cmd_ptr->cmd_id);

  if(status < 0 || TUI_CANCEL_PRESSED == status || TUI_MIDDLE_PRESSED == status|| TUI_LEFT_PRESSED == status){
	  if (cmd_ptr->cmd_id != SEC_UI_SAMPLE_CMD14_MSG_CLEAN_UP) {
		  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "point 0, status %d", status);
	  rsp_ptr->status = -1;
	  return;
	  }
  }


  rsp_ptr->status = 0;
  switch (cmd_ptr->cmd_id) {
    case SEC_UI_SAMPLE_CMD0_START_SEC_UI:
      start_disp_fullscreen(cmd_ptr, rsp_ptr);
	  secUiRegisterTouchCallback(&draw_dot);
      break;

    case SEC_UI_SAMPLE_CMD1_SHOW_IMAGE:
      show_image(cmd_ptr,rsp_ptr);
      break;

    case SEC_UI_SAMPLE_CMD2_STOP_DISP:
      retval = sec_ui_stop_disp();
      if (retval < 0) {
        rsp_ptr->status = retval;
      }
      sec_ui_free_app_buffer();
      break;

    case SEC_UI_SAMPLE_CMD3_SHOW_IMAGE_PTR:
      show_image_ptr(cmd_ptr, rsp_ptr);
      break;

    case SEC_UI_SAMPLE_CMD4_TEST_APP_BUFFER:
      rsp_ptr->status = test_app_buffer();
      break;

    case SEC_UI_SAMPLE_CMD10_GET_PIN:
    	rsp_ptr->status = start_pin_dialog();
    	break;

    case SEC_UI_SAMPLE_CMD11_LOGIN:
    	rsp_ptr->status = start_login_dialog();
    	break;

    case SEC_UI_SAMPLE_CMD12_MSG_PIN:

    	/* set the null terminator to treat the user input as a string */
    	if(MAX_INPUT_LEN_BYTES - 1 < received_pin_len){
    		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "cannot set the null terminator, received pin is too long");
    		rsp_ptr->status = -1;
    		break;
    	}
    	received_pin[received_pin_len] = '\0';

    	strlcpy((char*)msg, pin, MAX_MSG_LEN);
    	len = strlcat((char*)msg, (char*)received_pin, MAX_MSG_LEN);
    	if (len > MAX_MSG_LEN){
    		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "truncated response");
    		rsp_ptr->status = -1;
    	} else{
    		rsp_ptr->status = start_msg_dialog(msg, len);
    	}
    	break;

    case SEC_UI_SAMPLE_CMD13_MSG_LOGIN:
    	/* set the null terminator to treat the user input as a string */
    	if(MAX_INPUT_LEN_BYTES - 1 < received_username_len){
    		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "cannot set the null terminator, received username is too long");
    		break;
    	}
    	received_username[received_username_len] = '\0';

    	/* set the null terminator to treat the user input as a string */
    	if(MAX_INPUT_LEN_BYTES - 1 < received_password_len){
    		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "cannot set the null terminator, received password is too long");
    		break;
    	}
    	received_password[received_password_len] = '\0';

    	strlcpy((char*)msg, login_user, MAX_MSG_LEN);
    	strlcat((char*)msg, (char*)received_username, MAX_MSG_LEN);
    	strlcat((char*)msg, login_pass, MAX_MSG_LEN);
    	len = strlcat((char*)msg, (char*)received_password, MAX_MSG_LEN);
    	if(len > MAX_MSG_LEN){
    		QSEE_LOG(QSEE_LOG_MSG_DEBUG, "cannot call start_msg_dialog, msg is too long");
    		rsp_ptr->status = -1;
    		break;
    	}
    	QSEE_LOG(QSEE_LOG_MSG_DEBUG, "calling start_msg_dialog with msg = %s, len= %d", msg, len);
    	rsp_ptr->status = start_msg_dialog(msg,len);
    	break;

    case SEC_UI_SAMPLE_CMD14_MSG_CLEAN_UP:
    	qsee_tui_tear_down();
    	break;

    default:
      rsp_ptr->status = SEC_UI_NOT_SUPPORTED;
      QSEE_LOG(QSEE_LOG_MSG_DEBUG, "Unsupported command\n\n");
      break;
  }
}

void tz_app_shutdown(void)
{
  secUiTouchStop();
  int32_t status = sec_ui_hlos_release();
  QSEE_LOG(QSEE_LOG_MSG_DEBUG, "sec_ui_hlos_release returned %d", status);
  qsee_tui_release_secure_indicator();
  qsee_tui_tear_down();
  qsee_free(sec_ind_buffer);
  qsee_free(logo_buffer);
  sec_ui_free_app_buffer();
  return;
}
