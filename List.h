/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	List
**       Description :	List files
** **************************************************************************************/
#ifndef _LIST_H
#define _LIST_H
  /* /////////////////////////////// Interface Fns //////////////////////// */
  void List_vidInsert(strTCB_t** Copy_ppstrList, strTCB_t* Copy_pstrNode, enuOrderType_t Copy_enuOrderType);
  strTCB_t* List_pstrExtractHead(strTCB_t** Copy_ppstrList); 
  void List_vidDelete(strTCB_t** Copy_ppstrList, strTCB_t* Copy_pstrNode);
  /* ////////////////////////////////////////////////////////////////////// */
#endif