#pragma once


CLASS_DECL_ACME void main_async_runnable(::matter * pobjectTask);
CLASS_DECL_ACME void main_sync_runnable(::matter * pobjectTask, ::duration durationTimeout = one_minute());
CLASS_DECL_ACME void main_branch(::matter* pobjectTask, e_priority epriority);


::estatus run_task(::matter * pobjectTask);








template < typename PRED >
inline void main_async(PRED pred, e_priority epriority = priority_normal)
{

   async_pred(&main_branch, pred, epriority);

}


template < typename PRED >
inline void main_sync(PRED pred, ::duration durationTimeout = one_minute(), e_priority epriority = priority_normal)
{

   sync_pred(&main_branch, pred, durationTimeout, epriority);

}



