/*******************************************************************************
* File Name: I2CMASTER_INT.c
* Version 3.50
*
* Description:
*  This file provides the source code of Interrupt Service Routine (ISR)
*  for the I2C component.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2CMASTER_PVT.h"
#include "cyapicallbacks.h"


/*******************************************************************************
*  Place your includes, defines and code here.
********************************************************************************/
/* `#START I2CMASTER_ISR_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: I2CMASTER_ISR
********************************************************************************
*
* Summary:
*  The handler for the I2C interrupt. The slave and master operations are
*  handled here.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
CY_ISR(I2CMASTER_ISR)
{
#if (I2CMASTER_MODE_SLAVE_ENABLED)
   uint8  tmp8;
#endif  /* (I2CMASTER_MODE_SLAVE_ENABLED) */

    uint8  tmpCsr;
    
#ifdef I2CMASTER_ISR_ENTRY_CALLBACK
    I2CMASTER_ISR_EntryCallback();
#endif /* I2CMASTER_ISR_ENTRY_CALLBACK */
    

#if(I2CMASTER_TIMEOUT_FF_ENABLED)
    if(0u != I2CMASTER_TimeoutGetStatus())
    {
        I2CMASTER_TimeoutReset();
        I2CMASTER_state = I2CMASTER_SM_EXIT_IDLE;
        /* I2CMASTER_CSR_REG should be cleared after reset */
    }
#endif /* (I2CMASTER_TIMEOUT_FF_ENABLED) */


    tmpCsr = I2CMASTER_CSR_REG;      /* Make copy as interrupts clear */

#if(I2CMASTER_MODE_MULTI_MASTER_SLAVE_ENABLED)
    if(I2CMASTER_CHECK_START_GEN(I2CMASTER_MCSR_REG))
    {
        I2CMASTER_CLEAR_START_GEN;

        /* Set transfer complete and error flags */
        I2CMASTER_mstrStatus |= (I2CMASTER_MSTAT_ERR_XFER |
                                        I2CMASTER_GET_MSTAT_CMPLT);

        /* Slave was addressed */
        I2CMASTER_state = I2CMASTER_SM_SLAVE;
    }
#endif /* (I2CMASTER_MODE_MULTI_MASTER_SLAVE_ENABLED) */


#if(I2CMASTER_MODE_MULTI_MASTER_ENABLED)
    if(I2CMASTER_CHECK_LOST_ARB(tmpCsr))
    {
        /* Set errors */
        I2CMASTER_mstrStatus |= (I2CMASTER_MSTAT_ERR_XFER     |
                                        I2CMASTER_MSTAT_ERR_ARB_LOST |
                                        I2CMASTER_GET_MSTAT_CMPLT);

        I2CMASTER_DISABLE_INT_ON_STOP; /* Interrupt on Stop is enabled by write */

        #if(I2CMASTER_MODE_MULTI_MASTER_SLAVE_ENABLED)
            if(I2CMASTER_CHECK_ADDRESS_STS(tmpCsr))
            {
                /* Slave was addressed */
                I2CMASTER_state = I2CMASTER_SM_SLAVE;
            }
            else
            {
                I2CMASTER_BUS_RELEASE;

                I2CMASTER_state = I2CMASTER_SM_EXIT_IDLE;
            }
        #else
            I2CMASTER_BUS_RELEASE;

            I2CMASTER_state = I2CMASTER_SM_EXIT_IDLE;

        #endif /* (I2CMASTER_MODE_MULTI_MASTER_SLAVE_ENABLED) */
    }
#endif /* (I2CMASTER_MODE_MULTI_MASTER_ENABLED) */

    /* Check for master operation mode */
    if(I2CMASTER_CHECK_SM_MASTER)
    {
    #if(I2CMASTER_MODE_MASTER_ENABLED)
        if(I2CMASTER_CHECK_BYTE_COMPLETE(tmpCsr))
        {
            switch (I2CMASTER_state)
            {
            case I2CMASTER_SM_MSTR_WR_ADDR:  /* After address is sent, write data */
            case I2CMASTER_SM_MSTR_RD_ADDR:  /* After address is sent, read data */

                tmpCsr &= ((uint8) ~I2CMASTER_CSR_STOP_STATUS); /* Clear Stop bit history on address phase */

                if(I2CMASTER_CHECK_ADDR_ACK(tmpCsr))
                {
                    /* Setup for transmit or receive of data */
                    if(I2CMASTER_state == I2CMASTER_SM_MSTR_WR_ADDR)   /* TRANSMIT data */
                    {
                        /* Check if at least one byte to transfer */
                        if(I2CMASTER_mstrWrBufSize > 0u)
                        {
                            /* Load the 1st data byte */
                            I2CMASTER_DATA_REG = I2CMASTER_mstrWrBufPtr[0u];
                            I2CMASTER_TRANSMIT_DATA;
                            I2CMASTER_mstrWrBufIndex = 1u;   /* Set index to 2nd element */

                            /* Set transmit state until done */
                            I2CMASTER_state = I2CMASTER_SM_MSTR_WR_DATA;
                        }
                        /* End of buffer: complete writing */
                        else if(I2CMASTER_CHECK_NO_STOP(I2CMASTER_mstrControl))
                        {
                            /* Set write complete and master halted */
                            I2CMASTER_mstrStatus |= (I2CMASTER_MSTAT_XFER_HALT |
                                                            I2CMASTER_MSTAT_WR_CMPLT);

                            I2CMASTER_state = I2CMASTER_SM_MSTR_HALT; /* Expect ReStart */
                            I2CMASTER_DisableInt();
                        }
                        else
                        {
                            I2CMASTER_ENABLE_INT_ON_STOP; /* Enable interrupt on Stop, to catch it */
                            I2CMASTER_GENERATE_STOP;
                        }
                    }
                    else  /* Master receive data */
                    {
                        I2CMASTER_READY_TO_READ; /* Release bus to read data */

                        I2CMASTER_state  = I2CMASTER_SM_MSTR_RD_DATA;
                    }
                }
                /* Address is NACKed */
                else if(I2CMASTER_CHECK_ADDR_NAK(tmpCsr))
                {
                    /* Set Address NAK error */
                    I2CMASTER_mstrStatus |= (I2CMASTER_MSTAT_ERR_XFER |
                                                    I2CMASTER_MSTAT_ERR_ADDR_NAK);

                    if(I2CMASTER_CHECK_NO_STOP(I2CMASTER_mstrControl))
                    {
                        I2CMASTER_mstrStatus |= (I2CMASTER_MSTAT_XFER_HALT |
                                                        I2CMASTER_GET_MSTAT_CMPLT);

                        I2CMASTER_state = I2CMASTER_SM_MSTR_HALT; /* Expect RESTART */
                        I2CMASTER_DisableInt();
                    }
                    else  /* Do normal Stop */
                    {
                        I2CMASTER_ENABLE_INT_ON_STOP; /* Enable interrupt on Stop, to catch it */
                        I2CMASTER_GENERATE_STOP;
                    }
                }
                else
                {
                    /* Address phase is not set for some reason: error */
                    #if(I2CMASTER_TIMEOUT_ENABLED)
                        /* Exit interrupt to take chance for timeout timer to handle this case */
                        I2CMASTER_DisableInt();
                        I2CMASTER_ClearPendingInt();
                    #else
                        /* Block execution flow: unexpected condition */
                        CYASSERT(0u != 0u);
                    #endif /* (I2CMASTER_TIMEOUT_ENABLED) */
                }
                break;

            case I2CMASTER_SM_MSTR_WR_DATA:

                if(I2CMASTER_CHECK_DATA_ACK(tmpCsr))
                {
                    /* Check if end of buffer */
                    if(I2CMASTER_mstrWrBufIndex  < I2CMASTER_mstrWrBufSize)
                    {
                        I2CMASTER_DATA_REG =
                                                 I2CMASTER_mstrWrBufPtr[I2CMASTER_mstrWrBufIndex];
                        I2CMASTER_TRANSMIT_DATA;
                        I2CMASTER_mstrWrBufIndex++;
                    }
                    /* End of buffer: complete writing */
                    else if(I2CMASTER_CHECK_NO_STOP(I2CMASTER_mstrControl))
                    {
                        /* Set write complete and master halted */
                        I2CMASTER_mstrStatus |= (I2CMASTER_MSTAT_XFER_HALT |
                                                        I2CMASTER_MSTAT_WR_CMPLT);

                        I2CMASTER_state = I2CMASTER_SM_MSTR_HALT;    /* Expect restart */
                        I2CMASTER_DisableInt();
                    }
                    else  /* Do normal Stop */
                    {
                        I2CMASTER_ENABLE_INT_ON_STOP;    /* Enable interrupt on Stop, to catch it */
                        I2CMASTER_GENERATE_STOP;
                    }
                }
                /* Last byte NAKed: end writing */
                else if(I2CMASTER_CHECK_NO_STOP(I2CMASTER_mstrControl))
                {
                    /* Set write complete, short transfer and master halted */
                    I2CMASTER_mstrStatus |= (I2CMASTER_MSTAT_ERR_XFER       |
                                                    I2CMASTER_MSTAT_ERR_SHORT_XFER |
                                                    I2CMASTER_MSTAT_XFER_HALT      |
                                                    I2CMASTER_MSTAT_WR_CMPLT);

                    I2CMASTER_state = I2CMASTER_SM_MSTR_HALT;    /* Expect ReStart */
                    I2CMASTER_DisableInt();
                }
                else  /* Do normal Stop */
                {
                    I2CMASTER_ENABLE_INT_ON_STOP;    /* Enable interrupt on Stop, to catch it */
                    I2CMASTER_GENERATE_STOP;

                    /* Set short transfer and error flag */
                    I2CMASTER_mstrStatus |= (I2CMASTER_MSTAT_ERR_SHORT_XFER |
                                                    I2CMASTER_MSTAT_ERR_XFER);
                }

                break;

            case I2CMASTER_SM_MSTR_RD_DATA:

                I2CMASTER_mstrRdBufPtr[I2CMASTER_mstrRdBufIndex] = I2CMASTER_DATA_REG;
                I2CMASTER_mstrRdBufIndex++;

                /* Check if end of buffer */
                if(I2CMASTER_mstrRdBufIndex < I2CMASTER_mstrRdBufSize)
                {
                    I2CMASTER_ACK_AND_RECEIVE;       /* ACK and receive byte */
                }
                /* End of buffer: complete reading */
                else if(I2CMASTER_CHECK_NO_STOP(I2CMASTER_mstrControl))
                {
                    /* Set read complete and master halted */
                    I2CMASTER_mstrStatus |= (I2CMASTER_MSTAT_XFER_HALT |
                                                    I2CMASTER_MSTAT_RD_CMPLT);

                    I2CMASTER_state = I2CMASTER_SM_MSTR_HALT;    /* Expect ReStart */
                    I2CMASTER_DisableInt();
                }
                else
                {
                    I2CMASTER_ENABLE_INT_ON_STOP;
                    I2CMASTER_NAK_AND_RECEIVE;       /* NACK and TRY to generate Stop */
                }
                break;

            default: /* This is an invalid state and should not occur */

            #if(I2CMASTER_TIMEOUT_ENABLED)
                /* Exit interrupt to take chance for timeout timer to handles this case */
                I2CMASTER_DisableInt();
                I2CMASTER_ClearPendingInt();
            #else
                /* Block execution flow: unexpected condition */
                CYASSERT(0u != 0u);
            #endif /* (I2CMASTER_TIMEOUT_ENABLED) */

                break;
            }
        }

        /* Catches Stop: end of transaction */
        if(I2CMASTER_CHECK_STOP_STS(tmpCsr))
        {
            I2CMASTER_mstrStatus |= I2CMASTER_GET_MSTAT_CMPLT;

            I2CMASTER_DISABLE_INT_ON_STOP;
            I2CMASTER_state = I2CMASTER_SM_IDLE;
        }
    #endif /* (I2CMASTER_MODE_MASTER_ENABLED) */
    }
    else if(I2CMASTER_CHECK_SM_SLAVE)
    {
    #if(I2CMASTER_MODE_SLAVE_ENABLED)

        if((I2CMASTER_CHECK_STOP_STS(tmpCsr)) || /* Stop || Restart */
           (I2CMASTER_CHECK_BYTE_COMPLETE(tmpCsr) && I2CMASTER_CHECK_ADDRESS_STS(tmpCsr)))
        {
            /* Catch end of master write transaction: use interrupt on Stop */
            /* The Stop bit history on address phase does not have correct state */
            if(I2CMASTER_SM_SL_WR_DATA == I2CMASTER_state)
            {
                I2CMASTER_DISABLE_INT_ON_STOP;

                I2CMASTER_slStatus &= ((uint8) ~I2CMASTER_SSTAT_WR_BUSY);
                I2CMASTER_slStatus |= ((uint8)  I2CMASTER_SSTAT_WR_CMPLT);

                I2CMASTER_state = I2CMASTER_SM_IDLE;
            }
        }

        if(I2CMASTER_CHECK_BYTE_COMPLETE(tmpCsr))
        {
            /* The address only issued after Start or ReStart: so check the address
               to catch these events:
                FF : sets an address phase with a byte_complete interrupt trigger.
                UDB: sets an address phase immediately after Start or ReStart. */
            if(I2CMASTER_CHECK_ADDRESS_STS(tmpCsr))
            {
            /* Check for software address detection */
            #if(I2CMASTER_SW_ADRR_DECODE)
                tmp8 = I2CMASTER_GET_SLAVE_ADDR(I2CMASTER_DATA_REG);

                if(tmp8 == I2CMASTER_slAddress)   /* Check for address match */
                {
                    if(0u != (I2CMASTER_DATA_REG & I2CMASTER_READ_FLAG))
                    {
                        /* Place code to prepare read buffer here                  */
                        /* `#START I2CMASTER_SW_PREPARE_READ_BUF_interrupt` */

                        /* `#END` */

                    #ifdef I2CMASTER_SW_PREPARE_READ_BUF_CALLBACK
                        I2CMASTER_SwPrepareReadBuf_Callback();
                    #endif /* I2CMASTER_SW_PREPARE_READ_BUF_CALLBACK */
                        
                        /* Prepare next operation to read, get data and place in data register */
                        if(I2CMASTER_slRdBufIndex < I2CMASTER_slRdBufSize)
                        {
                            /* Load first data byte from array */
                            I2CMASTER_DATA_REG = I2CMASTER_slRdBufPtr[I2CMASTER_slRdBufIndex];
                            I2CMASTER_ACK_AND_TRANSMIT;
                            I2CMASTER_slRdBufIndex++;

                            I2CMASTER_slStatus |= I2CMASTER_SSTAT_RD_BUSY;
                        }
                        else    /* Overflow: provide 0xFF on bus */
                        {
                            I2CMASTER_DATA_REG = I2CMASTER_OVERFLOW_RETURN;
                            I2CMASTER_ACK_AND_TRANSMIT;

                            I2CMASTER_slStatus  |= (I2CMASTER_SSTAT_RD_BUSY |
                                                           I2CMASTER_SSTAT_RD_ERR_OVFL);
                        }

                        I2CMASTER_state = I2CMASTER_SM_SL_RD_DATA;
                    }
                    else  /* Write transaction: receive 1st byte */
                    {
                        I2CMASTER_ACK_AND_RECEIVE;
                        I2CMASTER_state = I2CMASTER_SM_SL_WR_DATA;

                        I2CMASTER_slStatus |= I2CMASTER_SSTAT_WR_BUSY;
                        I2CMASTER_ENABLE_INT_ON_STOP;
                    }
                }
                else
                {
                    /*     Place code to compare for additional address here    */
                    /* `#START I2CMASTER_SW_ADDR_COMPARE_interruptStart` */

                    /* `#END` */

                #ifdef I2CMASTER_SW_ADDR_COMPARE_ENTRY_CALLBACK
                    I2CMASTER_SwAddrCompare_EntryCallback();
                #endif /* I2CMASTER_SW_ADDR_COMPARE_ENTRY_CALLBACK */
                    
                    I2CMASTER_NAK_AND_RECEIVE;   /* NACK address */

                    /* Place code to end of condition for NACK generation here */
                    /* `#START I2CMASTER_SW_ADDR_COMPARE_interruptEnd`  */

                    /* `#END` */

                #ifdef I2CMASTER_SW_ADDR_COMPARE_EXIT_CALLBACK
                    I2CMASTER_SwAddrCompare_ExitCallback();
                #endif /* I2CMASTER_SW_ADDR_COMPARE_EXIT_CALLBACK */
                }

            #else /* (I2CMASTER_HW_ADRR_DECODE) */

                if(0u != (I2CMASTER_DATA_REG & I2CMASTER_READ_FLAG))
                {
                    /* Place code to prepare read buffer here                  */
                    /* `#START I2CMASTER_HW_PREPARE_READ_BUF_interrupt` */

                    /* `#END` */
                    
                #ifdef I2CMASTER_HW_PREPARE_READ_BUF_CALLBACK
                    I2CMASTER_HwPrepareReadBuf_Callback();
                #endif /* I2CMASTER_HW_PREPARE_READ_BUF_CALLBACK */

                    /* Prepare next operation to read, get data and place in data register */
                    if(I2CMASTER_slRdBufIndex < I2CMASTER_slRdBufSize)
                    {
                        /* Load first data byte from array */
                        I2CMASTER_DATA_REG = I2CMASTER_slRdBufPtr[I2CMASTER_slRdBufIndex];
                        I2CMASTER_ACK_AND_TRANSMIT;
                        I2CMASTER_slRdBufIndex++;

                        I2CMASTER_slStatus |= I2CMASTER_SSTAT_RD_BUSY;
                    }
                    else    /* Overflow: provide 0xFF on bus */
                    {
                        I2CMASTER_DATA_REG = I2CMASTER_OVERFLOW_RETURN;
                        I2CMASTER_ACK_AND_TRANSMIT;

                        I2CMASTER_slStatus  |= (I2CMASTER_SSTAT_RD_BUSY |
                                                       I2CMASTER_SSTAT_RD_ERR_OVFL);
                    }

                    I2CMASTER_state = I2CMASTER_SM_SL_RD_DATA;
                }
                else  /* Write transaction: receive 1st byte */
                {
                    I2CMASTER_ACK_AND_RECEIVE;
                    I2CMASTER_state = I2CMASTER_SM_SL_WR_DATA;

                    I2CMASTER_slStatus |= I2CMASTER_SSTAT_WR_BUSY;
                    I2CMASTER_ENABLE_INT_ON_STOP;
                }

            #endif /* (I2CMASTER_SW_ADRR_DECODE) */
            }
            /* Data states */
            /* Data master writes into slave */
            else if(I2CMASTER_state == I2CMASTER_SM_SL_WR_DATA)
            {
                if(I2CMASTER_slWrBufIndex < I2CMASTER_slWrBufSize)
                {
                    tmp8 = I2CMASTER_DATA_REG;
                    I2CMASTER_ACK_AND_RECEIVE;
                    I2CMASTER_slWrBufPtr[I2CMASTER_slWrBufIndex] = tmp8;
                    I2CMASTER_slWrBufIndex++;
                }
                else  /* of array: complete write, send NACK */
                {
                    I2CMASTER_NAK_AND_RECEIVE;

                    I2CMASTER_slStatus |= I2CMASTER_SSTAT_WR_ERR_OVFL;
                }
            }
            /* Data master reads from slave */
            else if(I2CMASTER_state == I2CMASTER_SM_SL_RD_DATA)
            {
                if(I2CMASTER_CHECK_DATA_ACK(tmpCsr))
                {
                    if(I2CMASTER_slRdBufIndex < I2CMASTER_slRdBufSize)
                    {
                         /* Get data from array */
                        I2CMASTER_DATA_REG = I2CMASTER_slRdBufPtr[I2CMASTER_slRdBufIndex];
                        I2CMASTER_TRANSMIT_DATA;
                        I2CMASTER_slRdBufIndex++;
                    }
                    else   /* Overflow: provide 0xFF on bus */
                    {
                        I2CMASTER_DATA_REG = I2CMASTER_OVERFLOW_RETURN;
                        I2CMASTER_TRANSMIT_DATA;

                        I2CMASTER_slStatus |= I2CMASTER_SSTAT_RD_ERR_OVFL;
                    }
                }
                else  /* Last byte was NACKed: read complete */
                {
                    /* Only NACK appears on bus */
                    I2CMASTER_DATA_REG = I2CMASTER_OVERFLOW_RETURN;
                    I2CMASTER_NAK_AND_TRANSMIT;

                    I2CMASTER_slStatus &= ((uint8) ~I2CMASTER_SSTAT_RD_BUSY);
                    I2CMASTER_slStatus |= ((uint8)  I2CMASTER_SSTAT_RD_CMPLT);

                    I2CMASTER_state = I2CMASTER_SM_IDLE;
                }
            }
            else
            {
            #if(I2CMASTER_TIMEOUT_ENABLED)
                /* Exit interrupt to take chance for timeout timer to handle this case */
                I2CMASTER_DisableInt();
                I2CMASTER_ClearPendingInt();
            #else
                /* Block execution flow: unexpected condition */
                CYASSERT(0u != 0u);
            #endif /* (I2CMASTER_TIMEOUT_ENABLED) */
            }
        }
    #endif /* (I2CMASTER_MODE_SLAVE_ENABLED) */
    }
    else
    {
        /* The FSM skips master and slave processing: return to IDLE */
        I2CMASTER_state = I2CMASTER_SM_IDLE;
    }

#ifdef I2CMASTER_ISR_EXIT_CALLBACK
    I2CMASTER_ISR_ExitCallback();
#endif /* I2CMASTER_ISR_EXIT_CALLBACK */    
}


#if ((I2CMASTER_FF_IMPLEMENTED) && (I2CMASTER_WAKEUP_ENABLED))
    /*******************************************************************************
    * Function Name: I2CMASTER_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  The interrupt handler to trigger after a wakeup.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(I2CMASTER_WAKEUP_ISR)
    {
    #ifdef I2CMASTER_WAKEUP_ISR_ENTRY_CALLBACK
        I2CMASTER_WAKEUP_ISR_EntryCallback();
    #endif /* I2CMASTER_WAKEUP_ISR_ENTRY_CALLBACK */
         
        /* Set flag to notify that matched address is received */
        I2CMASTER_wakeupSource = 1u;

        /* SCL is stretched until the I2C_Wake() is called */

    #ifdef I2CMASTER_WAKEUP_ISR_EXIT_CALLBACK
        I2CMASTER_WAKEUP_ISR_ExitCallback();
    #endif /* I2CMASTER_WAKEUP_ISR_EXIT_CALLBACK */
    }
#endif /* ((I2CMASTER_FF_IMPLEMENTED) && (I2CMASTER_WAKEUP_ENABLED)) */


/* [] END OF FILE */
