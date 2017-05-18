/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_RKHSMA_H
#define _MOCK_RKHSMA_H

#include "rkhsma.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void Mock_rkhsma_Init(void);
void Mock_rkhsma_Destroy(void);
void Mock_rkhsma_Verify(void);




#define rkh_sma_register_Ignore() rkh_sma_register_CMockIgnore()
void rkh_sma_register_CMockIgnore(void);
#define rkh_sma_register_Expect(me) rkh_sma_register_CMockExpect(__LINE__, me)
void rkh_sma_register_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* me);
typedef void (* CMOCK_rkh_sma_register_CALLBACK)(RKH_SMA_T* me, int cmock_num_calls);
void rkh_sma_register_StubWithCallback(CMOCK_rkh_sma_register_CALLBACK Callback);
#define rkh_sma_register_IgnoreArg_me() rkh_sma_register_CMockIgnoreArg_me(__LINE__)
void rkh_sma_register_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_unregister_Ignore() rkh_sma_unregister_CMockIgnore()
void rkh_sma_unregister_CMockIgnore(void);
#define rkh_sma_unregister_Expect(me) rkh_sma_unregister_CMockExpect(__LINE__, me)
void rkh_sma_unregister_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* me);
typedef void (* CMOCK_rkh_sma_unregister_CALLBACK)(RKH_SMA_T* me, int cmock_num_calls);
void rkh_sma_unregister_StubWithCallback(CMOCK_rkh_sma_unregister_CALLBACK Callback);
#define rkh_sma_unregister_IgnoreArg_me() rkh_sma_unregister_CMockIgnoreArg_me(__LINE__)
void rkh_sma_unregister_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_ctor_Ignore() rkh_sma_ctor_CMockIgnore()
void rkh_sma_ctor_CMockIgnore(void);
#define rkh_sma_ctor_Expect(me, vtbl) rkh_sma_ctor_CMockExpect(__LINE__, me, vtbl)
void rkh_sma_ctor_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* me, const RKHSmaVtbl* vtbl);
typedef void (* CMOCK_rkh_sma_ctor_CALLBACK)(RKH_SMA_T* me, const RKHSmaVtbl* vtbl, int cmock_num_calls);
void rkh_sma_ctor_StubWithCallback(CMOCK_rkh_sma_ctor_CALLBACK Callback);
#define rkh_sma_ctor_IgnoreArg_me() rkh_sma_ctor_CMockIgnoreArg_me(__LINE__)
void rkh_sma_ctor_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_ctor_IgnoreArg_vtbl() rkh_sma_ctor_CMockIgnoreArg_vtbl(__LINE__)
void rkh_sma_ctor_CMockIgnoreArg_vtbl(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_activate_Ignore() rkh_sma_activate_CMockIgnore()
void rkh_sma_activate_CMockIgnore(void);
#define rkh_sma_activate_Expect(me, qSto, qSize, stkSto, stkSize) rkh_sma_activate_CMockExpect(__LINE__, me, qSto, qSize, stkSto, stkSize)
void rkh_sma_activate_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* me, const RKH_EVT_T** qSto, RKH_RQNE_T qSize, void* stkSto, rui32_t stkSize);
typedef void (* CMOCK_rkh_sma_activate_CALLBACK)(RKH_SMA_T* me, const RKH_EVT_T** qSto, RKH_RQNE_T qSize, void* stkSto, rui32_t stkSize, int cmock_num_calls);
void rkh_sma_activate_StubWithCallback(CMOCK_rkh_sma_activate_CALLBACK Callback);
#define rkh_sma_activate_IgnoreArg_me() rkh_sma_activate_CMockIgnoreArg_me(__LINE__)
void rkh_sma_activate_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_activate_IgnoreArg_qSto() rkh_sma_activate_CMockIgnoreArg_qSto(__LINE__)
void rkh_sma_activate_CMockIgnoreArg_qSto(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_activate_IgnoreArg_qSize() rkh_sma_activate_CMockIgnoreArg_qSize(__LINE__)
void rkh_sma_activate_CMockIgnoreArg_qSize(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_activate_IgnoreArg_stkSto() rkh_sma_activate_CMockIgnoreArg_stkSto(__LINE__)
void rkh_sma_activate_CMockIgnoreArg_stkSto(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_activate_IgnoreArg_stkSize() rkh_sma_activate_CMockIgnoreArg_stkSize(__LINE__)
void rkh_sma_activate_CMockIgnoreArg_stkSize(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_terminate_Ignore() rkh_sma_terminate_CMockIgnore()
void rkh_sma_terminate_CMockIgnore(void);
#define rkh_sma_terminate_Expect(me) rkh_sma_terminate_CMockExpect(__LINE__, me)
void rkh_sma_terminate_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* me);
typedef void (* CMOCK_rkh_sma_terminate_CALLBACK)(RKH_SMA_T* me, int cmock_num_calls);
void rkh_sma_terminate_StubWithCallback(CMOCK_rkh_sma_terminate_CALLBACK Callback);
#define rkh_sma_terminate_IgnoreArg_me() rkh_sma_terminate_CMockIgnoreArg_me(__LINE__)
void rkh_sma_terminate_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_post_fifo_Ignore() rkh_sma_post_fifo_CMockIgnore()
void rkh_sma_post_fifo_CMockIgnore(void);
#define rkh_sma_post_fifo_Expect(me, e, sender) rkh_sma_post_fifo_CMockExpect(__LINE__, me, e, sender)
void rkh_sma_post_fifo_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* me, const RKH_EVT_T* e, const void* const sender);
typedef void (* CMOCK_rkh_sma_post_fifo_CALLBACK)(RKH_SMA_T* me, const RKH_EVT_T* e, const void* const sender, int cmock_num_calls);
void rkh_sma_post_fifo_StubWithCallback(CMOCK_rkh_sma_post_fifo_CALLBACK Callback);
#define rkh_sma_post_fifo_IgnoreArg_me() rkh_sma_post_fifo_CMockIgnoreArg_me(__LINE__)
void rkh_sma_post_fifo_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_post_fifo_IgnoreArg_e() rkh_sma_post_fifo_CMockIgnoreArg_e(__LINE__)
void rkh_sma_post_fifo_CMockIgnoreArg_e(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_post_fifo_IgnoreArg_sender() rkh_sma_post_fifo_CMockIgnoreArg_sender(__LINE__)
void rkh_sma_post_fifo_CMockIgnoreArg_sender(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_post_lifo_Ignore() rkh_sma_post_lifo_CMockIgnore()
void rkh_sma_post_lifo_CMockIgnore(void);
#define rkh_sma_post_lifo_Expect(me, e, sender) rkh_sma_post_lifo_CMockExpect(__LINE__, me, e, sender)
void rkh_sma_post_lifo_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* me, const RKH_EVT_T* e, const void* const sender);
typedef void (* CMOCK_rkh_sma_post_lifo_CALLBACK)(RKH_SMA_T* me, const RKH_EVT_T* e, const void* const sender, int cmock_num_calls);
void rkh_sma_post_lifo_StubWithCallback(CMOCK_rkh_sma_post_lifo_CALLBACK Callback);
#define rkh_sma_post_lifo_IgnoreArg_me() rkh_sma_post_lifo_CMockIgnoreArg_me(__LINE__)
void rkh_sma_post_lifo_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_post_lifo_IgnoreArg_e() rkh_sma_post_lifo_CMockIgnoreArg_e(__LINE__)
void rkh_sma_post_lifo_CMockIgnoreArg_e(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_post_lifo_IgnoreArg_sender() rkh_sma_post_lifo_CMockIgnoreArg_sender(__LINE__)
void rkh_sma_post_lifo_CMockIgnoreArg_sender(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_get_IgnoreAndReturn(cmock_retval) rkh_sma_get_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void rkh_sma_get_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RKH_EVT_T* cmock_to_return);
#define rkh_sma_get_ExpectAndReturn(me, cmock_retval) rkh_sma_get_CMockExpectAndReturn(__LINE__, me, cmock_retval)
void rkh_sma_get_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* me, RKH_EVT_T* cmock_to_return);
typedef RKH_EVT_T* (* CMOCK_rkh_sma_get_CALLBACK)(RKH_SMA_T* me, int cmock_num_calls);
void rkh_sma_get_StubWithCallback(CMOCK_rkh_sma_get_CALLBACK Callback);
#define rkh_sma_get_IgnoreArg_me() rkh_sma_get_CMockIgnoreArg_me(__LINE__)
void rkh_sma_get_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_defer_Ignore() rkh_sma_defer_CMockIgnore()
void rkh_sma_defer_CMockIgnore(void);
#define rkh_sma_defer_Expect(q, e) rkh_sma_defer_CMockExpect(__LINE__, q, e)
void rkh_sma_defer_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_QUEUE_T* q, const RKH_EVT_T* e);
typedef void (* CMOCK_rkh_sma_defer_CALLBACK)(RKH_QUEUE_T* q, const RKH_EVT_T* e, int cmock_num_calls);
void rkh_sma_defer_StubWithCallback(CMOCK_rkh_sma_defer_CALLBACK Callback);
#define rkh_sma_defer_IgnoreArg_q() rkh_sma_defer_CMockIgnoreArg_q(__LINE__)
void rkh_sma_defer_CMockIgnoreArg_q(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_defer_IgnoreArg_e() rkh_sma_defer_CMockIgnoreArg_e(__LINE__)
void rkh_sma_defer_CMockIgnoreArg_e(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_recall_IgnoreAndReturn(cmock_retval) rkh_sma_recall_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void rkh_sma_recall_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, RKH_EVT_T* cmock_to_return);
#define rkh_sma_recall_ExpectAndReturn(me, q, cmock_retval) rkh_sma_recall_CMockExpectAndReturn(__LINE__, me, q, cmock_retval)
void rkh_sma_recall_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* me, RKH_QUEUE_T* q, RKH_EVT_T* cmock_to_return);
typedef RKH_EVT_T* (* CMOCK_rkh_sma_recall_CALLBACK)(RKH_SMA_T* me, RKH_QUEUE_T* q, int cmock_num_calls);
void rkh_sma_recall_StubWithCallback(CMOCK_rkh_sma_recall_CALLBACK Callback);
#define rkh_sma_recall_IgnoreArg_me() rkh_sma_recall_CMockIgnoreArg_me(__LINE__)
void rkh_sma_recall_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_recall_IgnoreArg_q() rkh_sma_recall_CMockIgnoreArg_q(__LINE__)
void rkh_sma_recall_CMockIgnoreArg_q(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_clear_info_Ignore() rkh_sma_clear_info_CMockIgnore()
void rkh_sma_clear_info_CMockIgnore(void);
#define rkh_sma_clear_info_Expect(me) rkh_sma_clear_info_CMockExpect(__LINE__, me)
void rkh_sma_clear_info_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* me);
typedef void (* CMOCK_rkh_sma_clear_info_CALLBACK)(RKH_SMA_T* me, int cmock_num_calls);
void rkh_sma_clear_info_StubWithCallback(CMOCK_rkh_sma_clear_info_CALLBACK Callback);
#define rkh_sma_clear_info_IgnoreArg_me() rkh_sma_clear_info_CMockIgnoreArg_me(__LINE__)
void rkh_sma_clear_info_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_get_info_Ignore() rkh_sma_get_info_CMockIgnore()
void rkh_sma_get_info_CMockIgnore(void);
#define rkh_sma_get_info_Expect(me, psi) rkh_sma_get_info_CMockExpect(__LINE__, me, psi)
void rkh_sma_get_info_CMockExpect(UNITY_LINE_TYPE cmock_line, RKH_SMA_T* me, RKH_SMAI_T* psi);
typedef void (* CMOCK_rkh_sma_get_info_CALLBACK)(RKH_SMA_T* me, RKH_SMAI_T* psi, int cmock_num_calls);
void rkh_sma_get_info_StubWithCallback(CMOCK_rkh_sma_get_info_CALLBACK Callback);
#define rkh_sma_get_info_IgnoreArg_me() rkh_sma_get_info_CMockIgnoreArg_me(__LINE__)
void rkh_sma_get_info_CMockIgnoreArg_me(UNITY_LINE_TYPE cmock_line);
#define rkh_sma_get_info_IgnoreArg_psi() rkh_sma_get_info_CMockIgnoreArg_psi(__LINE__)
void rkh_sma_get_info_CMockIgnoreArg_psi(UNITY_LINE_TYPE cmock_line);

#endif