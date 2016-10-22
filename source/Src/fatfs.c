/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "fatfs.h"
#include "main.h"



/* USER CODE BEGIN Variables */

/* USER CODE END Variables */    

uint8_t MX_FATFS_Init(void) 
{
	uint8_t retSD = true;    /* Return value for SD */
	MX_SDIO_SD_Init();
	
    /*## FatFS: Link the SD driver ###########################*/
    retSD = FATFS_LinkDriver(&SD_Driver, SDPath);
	if(retSD != 0)
	{
		printf("FatFs Link Driver Err\r\n");
        retSD = false;
	}
    else
    {
        retSD = true;
    }
    
    /*##-1- Register the file system object to the FatFs module ##############*/
    if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) != FR_OK)
    {
        #ifdef Debug_FatFs_Driver
            /* FatFs Initialization Error */
            printf("f_mount Err in fatfs_shell\r\n"); 
        #endif
        retSD = false;
        /*##-2- Create a FAT file system (format) on the logical drive #########*/
        /* WARNING: Formatting the uSD card will delete all content on the device */
        if(f_mkfs((TCHAR const*)SDPath, 0, 0) != FR_OK)
        {
            /* FatFs Format Error */
            #ifdef Debug_FatFs_Driver
                printf("FatFs Format Err in fatfs_shell\r\n");
            #endif
            retSD = false;
        }
        #ifdef Debug_FatFs_Driver
        else
        {
            printf("FatFs Format OK\r\n");
        }
        #endif
    }
    #ifdef Debug_FatFs_Driver
    else
    {
        printf("Register FS OK\r\n");
    }
    #endif
    
    return retSD;
}

/**
  * @brief  scan_filesìө֒·޶Ђ̹Ԑτݾ
  * @param  char* path 
  * @retval FRESULT
  */
FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;

    res = f_opendir(&dir, path);                        /* Open the directory */
    if (res == FR_OK) 
	{
        for (;;) 
		{
            res = f_readdir(&dir, &fno);                /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0)
			{
				break;  								/* Break on error or end of dir */
			}
            if (fno.fattrib & AM_DIR)  					/* It is a directory */
			{                    
                i = strlen(path);
                sprintf(&path[i], "/%s", fno.fname);
                res = scan_files(path);                 /* Enter the directory */
                if (res != FR_OK) break;
                path[i] = 0;
            } 
			else 
			{                                           /* It is a file. */
                printf("%s/%s\n", path, fno.fname);
            }
        }
        f_closedir(&dir);
    }

    return res;
}

/**
  * @brief  Test for FatFs,write and read data with SD 
  * @param  None
  * @retval None
  */
void FatFS_Test(void)
{
    FRESULT res;                                          /* FatFs function common result code */
    uint32_t byteswritten, bytesread;                     /* File write/read counts */
    uint8_t wtext[] = "This is STM32 working with FatFs"; /* File write buffer */
    uint8_t rtext[100];                                   /* File read buffer */    
    
    
    /*##-1- Register the file system object to the FatFs module ##############*/
    if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) != FR_OK)
    {
        /* FatFs Initialization Error */
        printf("f_mount Err\r\n"); 
    }
    else  
    {
        /*##-2- Create a FAT file system (format) on the logical drive #########*/
        /* WARNING: Formatting the uSD card will delete all content on the device */
        if(f_mkfs((TCHAR const*)SDPath, 0, 0) != FR_OK)
        {
            /* FatFs Format Error */
            printf("FatFs Format Err\r\n");
        }
        else
        {
            /*##-3- Create and Open a new text file object with write access #####*/
            if(f_open(&MyFile, "STM32.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
            {
                /* 'STM32.TXT' file Open for write Error */
                printf("f_open Err\r\n");
            }
            else
            {
                /*##-4- Write data to the text file ################################*/
                res = f_write(&MyFile, wtext, sizeof(wtext), (void *)&byteswritten);

                if((byteswritten == 0) || (res != FR_OK))
                {
                    /* 'STM32.TXT' file Write or EOF Error */
                    printf("f_write Err\r\n");
                }
                else
                {
                    /*##-5- Close the open text file #################################*/
                    f_close(&MyFile);

                    /*##-6- Open the text file object with read access ###############*/
                    if(f_open(&MyFile, "STM32.TXT", FA_READ) != FR_OK)
                    {
                        /* 'STM32.TXT' file Open for read Error */
                        printf("f_open Err in Read\r\n");
                    }
                    else
                    {
                        /*##-7- Read data from the text file ###########################*/
                        res = f_read(&MyFile, rtext, sizeof(rtext), (UINT*)&bytesread);

                        if((bytesread == 0) || (res != FR_OK))
                        {
                            /* 'STM32.TXT' file Read or EOF Error */
                            printf("f_read Err\r\n");
                        }
                        else
                        {
                            /*##-8- Close the open text file #############################*/
                            f_close(&MyFile);

                            /*##-9- Compare read data with the expected data ############*/
                            if ((bytesread != byteswritten))
                            {                
                                /* Read data is different from the expected data */
                                printf("read data err\r\n");
                            }
                            else
                            {
                                /* Success of the demo: no error occurrence */
                                printf("read data OK\r\n");
                            }
                        }
                    }
                }
            }
        }
    }
}


/**
  * @brief  Gets Time from RTC 
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
    DWORD date = 0;
    RTC_DateTypeDef date_s;
    RTC_TimeTypeDef rtc_time;
    
    Calendar_Get(&date_s,&rtc_time);
    
    date_s.Year = (date_s.Year + 2000) - 1980;  //????1980??
    date_s.Month = date_s.Month;     //0-11???1-12?
    rtc_time.Seconds /= 2;       //?????0-29
    
    date = 0;
    date = (date_s.Year << 25) | (date_s.Month<<21) | (date_s.Date<<16)|\
            (rtc_time.Hours<<11) | (rtc_time.Minutes<<5) | (rtc_time.Seconds);

    return date;
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
