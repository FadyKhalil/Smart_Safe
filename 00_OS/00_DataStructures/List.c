/* **************************************************************************************
**       Author      :	Michael S. Ibrahim
**       Date        :	May 27, 2022
**       Version     :	V01
**       SWC         :	List
**       Description :	List files
** **************************************************************************************/
/* ////////////////////////////// Headers ////////////////////////// */
/* LIB */
#include "StdTypes.h"
/* Own headers */
#include "List.h"
/* ////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////// Interface Fns //////////////////////// */
void List_vidInsert(strTCB_t** Copy_ppstrList, strTCB_t* Copy_pstrNode, enuOrderType_t Copy_enuOrderType)
{
  strTCB_t* Loc_pstrTraverser = *Copy_ppstrList;
  if((Copy_ppstrList != NULL) && (Copy_pstrNode != NULL))    
  {
    if(*Copy_ppstrList == NULL) /* The list is empty */
    {
      *Copy_ppstrList = Copy_pstrNode;
      Copy_pstrNode->Next = NULL;
      Copy_pstrNode->Prev = NULL;
    }/* if */
    else /* We have at least one node in the list */
    {
      if(Copy_enuOrderType == enuOrderType_Pri)
      {
        if(Copy_pstrNode->TaskPri < ((*Copy_ppstrList)->TaskPri))
        {
          Copy_pstrNode->Next = *Copy_ppstrList;
          Copy_pstrNode->Prev = NULL;
          (*Copy_ppstrList)->Prev = Copy_pstrNode;
          *Copy_ppstrList = Copy_pstrNode;
        }/* if */
        else
        {
          while((Loc_pstrTraverser->Next != NULL) && (Loc_pstrTraverser->Next->TaskPri < Copy_pstrNode->TaskPri))
          {
            Loc_pstrTraverser = Loc_pstrTraverser->Next;
          }/* while */
          Copy_pstrNode->Next = Loc_pstrTraverser->Next;
          Copy_pstrNode->Prev = Loc_pstrTraverser;
          Loc_pstrTraverser->Next = Copy_pstrNode;
          if(Copy_pstrNode->Next != NULL)
          {
            Copy_pstrNode->Next->Prev = Copy_pstrNode;
          }/* if */
        }/* else */
      }/* if */
      else if(Copy_enuOrderType == enuOrderType_Tick)
      {
        if(Copy_pstrNode->WaitTicks < ((*Copy_ppstrList)->WaitTicks))
        {
          Copy_pstrNode->Next = *Copy_ppstrList;
          Copy_pstrNode->Prev = NULL;
          (*Copy_ppstrList)->Prev = Copy_pstrNode;
          *Copy_ppstrList = Copy_pstrNode;
        }/* if */
        else
        {
          while((Loc_pstrTraverser->Next != NULL) && (Loc_pstrTraverser->Next->WaitTicks < Copy_pstrNode->WaitTicks))
          {
            Loc_pstrTraverser = Loc_pstrTraverser->Next;
          }/* while */
          Copy_pstrNode->Next = Loc_pstrTraverser->Next;
          Copy_pstrNode->Prev = Loc_pstrTraverser;
          Loc_pstrTraverser->Next = Copy_pstrNode;
          if(Copy_pstrNode->Next != NULL)
          {
            Copy_pstrNode->Next->Prev = Copy_pstrNode;
          }/* if */
        }/* else */
      }/* else if */
      else
      {
        /* MISRA */
      }/* else */
    }/* else */
  }/* if */
}/* List_vidInsert */
strTCB_t* List_pstrExtractHead(strTCB_t** Copy_ppstrList)
{
  strTCB_t* Loc_pstrHead = NULL;
  if((Copy_ppstrList != NULL) && (*Copy_ppstrList != NULL))
  {
    Loc_pstrHead = *Copy_ppstrList;
    *Copy_ppstrList = (*Copy_ppstrList)->Next;
    Loc_pstrHead->Next = NULL;
    if(*Copy_ppstrList != NULL)
    {
      (*Copy_ppstrList)->Prev = NULL;
    }/* if */
  }/* if */

  return(Loc_pstrHead);
}/* List_pstrExtractHead */
/* ////////////////////////////////////////////////////////////////////// */
