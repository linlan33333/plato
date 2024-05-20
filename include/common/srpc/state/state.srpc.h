#pragma once
#include <stdio.h>
#include <string>
#include "srpc/rpc_define.h"
#include "state.pb.h"

namespace State
{

/*
 * Server codes
 * Generated by SRPC
 */

class Service : public srpc::RPCService
{
public:
	// please implement these methods in server.cc

	virtual void CancelConn(StateRequest *request, StateResponse *response,
					srpc::RPCContext *ctx) = 0;

	virtual void SendMsg(StateRequest *request, StateResponse *response,
					srpc::RPCContext *ctx) = 0;

public:
	Service();
};

/*
 * Client codes
 * Generated by SRPC
 */

using CancelConnDone = std::function<void (StateResponse *, srpc::RPCContext *)>;
using SendMsgDone = std::function<void (StateResponse *, srpc::RPCContext *)>;

class SRPCClient : public srpc::SRPCClient
{
public:
	void CancelConn(const StateRequest *req, CancelConnDone done);
	void CancelConn(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx);
	WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> async_CancelConn(const StateRequest *req);

	void SendMsg(const StateRequest *req, SendMsgDone done);
	void SendMsg(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx);
	WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> async_SendMsg(const StateRequest *req);

public:
	SRPCClient(const char *host, unsigned short port);
	SRPCClient(const struct srpc::RPCClientParams *params);

public:
	srpc::SRPCClientTask *create_CancelConn_task(CancelConnDone done);
	srpc::SRPCClientTask *create_SendMsg_task(SendMsgDone done);
};

class SRPCHttpClient : public srpc::SRPCHttpClient
{
public:
	void CancelConn(const StateRequest *req, CancelConnDone done);
	void CancelConn(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx);
	WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> async_CancelConn(const StateRequest *req);

	void SendMsg(const StateRequest *req, SendMsgDone done);
	void SendMsg(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx);
	WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> async_SendMsg(const StateRequest *req);

public:
	SRPCHttpClient(const char *host, unsigned short port);
	SRPCHttpClient(const struct srpc::RPCClientParams *params);

public:
	srpc::SRPCHttpClientTask *create_CancelConn_task(CancelConnDone done);
	srpc::SRPCHttpClientTask *create_SendMsg_task(SendMsgDone done);
};

class BRPCClient : public srpc::BRPCClient
{
public:
	void CancelConn(const StateRequest *req, CancelConnDone done);
	void CancelConn(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx);
	WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> async_CancelConn(const StateRequest *req);

	void SendMsg(const StateRequest *req, SendMsgDone done);
	void SendMsg(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx);
	WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> async_SendMsg(const StateRequest *req);

public:
	BRPCClient(const char *host, unsigned short port);
	BRPCClient(const struct srpc::RPCClientParams *params);

public:
	srpc::BRPCClientTask *create_CancelConn_task(CancelConnDone done);
	srpc::BRPCClientTask *create_SendMsg_task(SendMsgDone done);
};

class TRPCClient : public srpc::TRPCClient
{
public:
	void CancelConn(const StateRequest *req, CancelConnDone done);
	void CancelConn(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx);
	WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> async_CancelConn(const StateRequest *req);

	void SendMsg(const StateRequest *req, SendMsgDone done);
	void SendMsg(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx);
	WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> async_SendMsg(const StateRequest *req);

public:
	TRPCClient(const char *host, unsigned short port);
	TRPCClient(const struct srpc::RPCClientParams *params);

public:
	srpc::TRPCClientTask *create_CancelConn_task(CancelConnDone done);
	srpc::TRPCClientTask *create_SendMsg_task(SendMsgDone done);
};

class TRPCHttpClient : public srpc::TRPCHttpClient
{
public:
	void CancelConn(const StateRequest *req, CancelConnDone done);
	void CancelConn(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx);
	WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> async_CancelConn(const StateRequest *req);

	void SendMsg(const StateRequest *req, SendMsgDone done);
	void SendMsg(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx);
	WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> async_SendMsg(const StateRequest *req);

public:
	TRPCHttpClient(const char *host, unsigned short port);
	TRPCHttpClient(const struct srpc::RPCClientParams *params);

public:
	srpc::TRPCHttpClientTask *create_CancelConn_task(CancelConnDone done);
	srpc::TRPCHttpClientTask *create_SendMsg_task(SendMsgDone done);
};

///// implements detials /////

inline Service::Service(): srpc::RPCService("State")
{
	this->srpc::RPCService::add_method("CancelConn",
		[this](srpc::RPCWorker& worker) ->int {
			return ServiceRPCCallImpl(this, worker, &Service::CancelConn);
		});

	this->srpc::RPCService::add_method("SendMsg",
		[this](srpc::RPCWorker& worker) ->int {
			return ServiceRPCCallImpl(this, worker, &Service::SendMsg);
		});
}

inline SRPCClient::SRPCClient(const char *host, unsigned short port):
	srpc::SRPCClient("State")
{
	struct srpc::RPCClientParams params = srpc::RPC_CLIENT_PARAMS_DEFAULT;
	
	params.host = host;
	params.port = port;
	this->srpc::SRPCClient::init(&params);
}

inline SRPCClient::SRPCClient(const struct srpc::RPCClientParams *params):
	srpc::SRPCClient("State")
{
	const struct srpc::RPCClientParams *temp = params;
	struct srpc::RPCClientParams temp_params;
	
	this->srpc::SRPCClient::init(temp);
}

inline void SRPCClient::CancelConn(const StateRequest *req, CancelConnDone done)
{
	auto *task = this->create_rpc_client_task("CancelConn", std::move(done));

	task->serialize_input(req);
	task->start();
}

inline void SRPCClient::CancelConn(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx)
{
	auto res = this->async_CancelConn(req).get();

	if (resp && res.second.success)
		*resp = std::move(res.first);

	if (sync_ctx)
		*sync_ctx = std::move(res.second);
}

inline WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> SRPCClient::async_CancelConn(const StateRequest *req)
{
	using RESULT = std::pair<StateResponse, srpc::RPCSyncContext>;
	auto *pr = new WFPromise<RESULT>();
	auto fr = pr->get_future();
	auto *task = this->create_rpc_client_task<StateResponse>("CancelConn", srpc::RPCAsyncFutureCallback<StateResponse>);

	task->serialize_input(req);
	task->user_data = pr;
	task->start();
	return fr;
}

inline void SRPCClient::SendMsg(const StateRequest *req, SendMsgDone done)
{
	auto *task = this->create_rpc_client_task("SendMsg", std::move(done));

	task->serialize_input(req);
	task->start();
}

inline void SRPCClient::SendMsg(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx)
{
	auto res = this->async_SendMsg(req).get();

	if (resp && res.second.success)
		*resp = std::move(res.first);

	if (sync_ctx)
		*sync_ctx = std::move(res.second);
}

inline WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> SRPCClient::async_SendMsg(const StateRequest *req)
{
	using RESULT = std::pair<StateResponse, srpc::RPCSyncContext>;
	auto *pr = new WFPromise<RESULT>();
	auto fr = pr->get_future();
	auto *task = this->create_rpc_client_task<StateResponse>("SendMsg", srpc::RPCAsyncFutureCallback<StateResponse>);

	task->serialize_input(req);
	task->user_data = pr;
	task->start();
	return fr;
}

inline srpc::SRPCClientTask *SRPCClient::create_CancelConn_task(CancelConnDone done)
{
	return this->create_rpc_client_task("CancelConn", std::move(done));
}

inline srpc::SRPCClientTask *SRPCClient::create_SendMsg_task(SendMsgDone done)
{
	return this->create_rpc_client_task("SendMsg", std::move(done));
}

inline SRPCHttpClient::SRPCHttpClient(const char *host, unsigned short port):
	srpc::SRPCHttpClient("State")
{
	struct srpc::RPCClientParams params = srpc::RPC_CLIENT_PARAMS_DEFAULT;
	
	params.host = host;
	params.port = port;
	this->srpc::SRPCHttpClient::init(&params);
}

inline SRPCHttpClient::SRPCHttpClient(const struct srpc::RPCClientParams *params):
	srpc::SRPCHttpClient("State")
{
	const struct srpc::RPCClientParams *temp = params;
	struct srpc::RPCClientParams temp_params;
	
	this->srpc::SRPCHttpClient::init(temp);
}

inline void SRPCHttpClient::CancelConn(const StateRequest *req, CancelConnDone done)
{
	auto *task = this->create_rpc_client_task("CancelConn", std::move(done));

	task->serialize_input(req);
	task->start();
}

inline void SRPCHttpClient::CancelConn(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx)
{
	auto res = this->async_CancelConn(req).get();

	if (resp && res.second.success)
		*resp = std::move(res.first);

	if (sync_ctx)
		*sync_ctx = std::move(res.second);
}

inline WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> SRPCHttpClient::async_CancelConn(const StateRequest *req)
{
	using RESULT = std::pair<StateResponse, srpc::RPCSyncContext>;
	auto *pr = new WFPromise<RESULT>();
	auto fr = pr->get_future();
	auto *task = this->create_rpc_client_task<StateResponse>("CancelConn", srpc::RPCAsyncFutureCallback<StateResponse>);

	task->serialize_input(req);
	task->user_data = pr;
	task->start();
	return fr;
}

inline void SRPCHttpClient::SendMsg(const StateRequest *req, SendMsgDone done)
{
	auto *task = this->create_rpc_client_task("SendMsg", std::move(done));

	task->serialize_input(req);
	task->start();
}

inline void SRPCHttpClient::SendMsg(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx)
{
	auto res = this->async_SendMsg(req).get();

	if (resp && res.second.success)
		*resp = std::move(res.first);

	if (sync_ctx)
		*sync_ctx = std::move(res.second);
}

inline WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> SRPCHttpClient::async_SendMsg(const StateRequest *req)
{
	using RESULT = std::pair<StateResponse, srpc::RPCSyncContext>;
	auto *pr = new WFPromise<RESULT>();
	auto fr = pr->get_future();
	auto *task = this->create_rpc_client_task<StateResponse>("SendMsg", srpc::RPCAsyncFutureCallback<StateResponse>);

	task->serialize_input(req);
	task->user_data = pr;
	task->start();
	return fr;
}

inline srpc::SRPCHttpClientTask *SRPCHttpClient::create_CancelConn_task(CancelConnDone done)
{
	return this->create_rpc_client_task("CancelConn", std::move(done));
}

inline srpc::SRPCHttpClientTask *SRPCHttpClient::create_SendMsg_task(SendMsgDone done)
{
	return this->create_rpc_client_task("SendMsg", std::move(done));
}

inline BRPCClient::BRPCClient(const char *host, unsigned short port):
	srpc::BRPCClient("State")
{
	struct srpc::RPCClientParams params = srpc::RPC_CLIENT_PARAMS_DEFAULT;
	
	params.host = host;
	params.port = port;
	this->srpc::BRPCClient::init(&params);
}

inline BRPCClient::BRPCClient(const struct srpc::RPCClientParams *params):
	srpc::BRPCClient("State")
{
	const struct srpc::RPCClientParams *temp = params;
	struct srpc::RPCClientParams temp_params;
	
	this->srpc::BRPCClient::init(temp);
}

inline void BRPCClient::CancelConn(const StateRequest *req, CancelConnDone done)
{
	auto *task = this->create_rpc_client_task("CancelConn", std::move(done));

	task->serialize_input(req);
	task->start();
}

inline void BRPCClient::CancelConn(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx)
{
	auto res = this->async_CancelConn(req).get();

	if (resp && res.second.success)
		*resp = std::move(res.first);

	if (sync_ctx)
		*sync_ctx = std::move(res.second);
}

inline WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> BRPCClient::async_CancelConn(const StateRequest *req)
{
	using RESULT = std::pair<StateResponse, srpc::RPCSyncContext>;
	auto *pr = new WFPromise<RESULT>();
	auto fr = pr->get_future();
	auto *task = this->create_rpc_client_task<StateResponse>("CancelConn", srpc::RPCAsyncFutureCallback<StateResponse>);

	task->serialize_input(req);
	task->user_data = pr;
	task->start();
	return fr;
}

inline void BRPCClient::SendMsg(const StateRequest *req, SendMsgDone done)
{
	auto *task = this->create_rpc_client_task("SendMsg", std::move(done));

	task->serialize_input(req);
	task->start();
}

inline void BRPCClient::SendMsg(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx)
{
	auto res = this->async_SendMsg(req).get();

	if (resp && res.second.success)
		*resp = std::move(res.first);

	if (sync_ctx)
		*sync_ctx = std::move(res.second);
}

inline WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> BRPCClient::async_SendMsg(const StateRequest *req)
{
	using RESULT = std::pair<StateResponse, srpc::RPCSyncContext>;
	auto *pr = new WFPromise<RESULT>();
	auto fr = pr->get_future();
	auto *task = this->create_rpc_client_task<StateResponse>("SendMsg", srpc::RPCAsyncFutureCallback<StateResponse>);

	task->serialize_input(req);
	task->user_data = pr;
	task->start();
	return fr;
}

inline srpc::BRPCClientTask *BRPCClient::create_CancelConn_task(CancelConnDone done)
{
	return this->create_rpc_client_task("CancelConn", std::move(done));
}

inline srpc::BRPCClientTask *BRPCClient::create_SendMsg_task(SendMsgDone done)
{
	return this->create_rpc_client_task("SendMsg", std::move(done));
}

inline TRPCClient::TRPCClient(const char *host, unsigned short port):
	srpc::TRPCClient("State")
{
	struct srpc::RPCClientParams params = srpc::RPC_CLIENT_PARAMS_DEFAULT;
	
	params.host = host;
	params.port = port;
	this->srpc::TRPCClient::init(&params);
}

inline TRPCClient::TRPCClient(const struct srpc::RPCClientParams *params):
	srpc::TRPCClient("State")
{
	const struct srpc::RPCClientParams *temp = params;
	struct srpc::RPCClientParams temp_params;
	
	this->srpc::TRPCClient::init(temp);
}

inline void TRPCClient::CancelConn(const StateRequest *req, CancelConnDone done)
{
	auto *task = this->create_rpc_client_task("/State/CancelConn", std::move(done));

	if (this->params.callee_timeout >= 0)
		task->get_req()->set_callee_timeout(this->params.callee_timeout);
	if (!this->params.caller.empty())
		task->get_req()->set_caller_name(this->params.caller);
	task->serialize_input(req);
	task->start();
}

inline void TRPCClient::CancelConn(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx)
{
	auto res = this->async_CancelConn(req).get();

	if (resp && res.second.success)
		*resp = std::move(res.first);

	if (sync_ctx)
		*sync_ctx = std::move(res.second);
}

inline WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> TRPCClient::async_CancelConn(const StateRequest *req)
{
	using RESULT = std::pair<StateResponse, srpc::RPCSyncContext>;
	auto *pr = new WFPromise<RESULT>();
	auto fr = pr->get_future();
	auto *task = this->create_rpc_client_task<StateResponse>("/State/CancelConn", srpc::RPCAsyncFutureCallback<StateResponse>);

	if (this->params.callee_timeout >= 0)
		task->get_req()->set_callee_timeout(this->params.callee_timeout);
	if (!this->params.caller.empty())
		task->get_req()->set_caller_name(this->params.caller);
	task->serialize_input(req);
	task->user_data = pr;
	task->start();
	return fr;
}

inline void TRPCClient::SendMsg(const StateRequest *req, SendMsgDone done)
{
	auto *task = this->create_rpc_client_task("/State/SendMsg", std::move(done));

	if (this->params.callee_timeout >= 0)
		task->get_req()->set_callee_timeout(this->params.callee_timeout);
	if (!this->params.caller.empty())
		task->get_req()->set_caller_name(this->params.caller);
	task->serialize_input(req);
	task->start();
}

inline void TRPCClient::SendMsg(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx)
{
	auto res = this->async_SendMsg(req).get();

	if (resp && res.second.success)
		*resp = std::move(res.first);

	if (sync_ctx)
		*sync_ctx = std::move(res.second);
}

inline WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> TRPCClient::async_SendMsg(const StateRequest *req)
{
	using RESULT = std::pair<StateResponse, srpc::RPCSyncContext>;
	auto *pr = new WFPromise<RESULT>();
	auto fr = pr->get_future();
	auto *task = this->create_rpc_client_task<StateResponse>("/State/SendMsg", srpc::RPCAsyncFutureCallback<StateResponse>);

	if (this->params.callee_timeout >= 0)
		task->get_req()->set_callee_timeout(this->params.callee_timeout);
	if (!this->params.caller.empty())
		task->get_req()->set_caller_name(this->params.caller);
	task->serialize_input(req);
	task->user_data = pr;
	task->start();
	return fr;
}

inline srpc::TRPCClientTask *TRPCClient::create_CancelConn_task(CancelConnDone done)
{
	auto *task = this->create_rpc_client_task("/State/CancelConn", std::move(done));

	if (!this->params.caller.empty())
		task->get_req()->set_caller_name(this->params.caller);

	return task;
}

inline srpc::TRPCClientTask *TRPCClient::create_SendMsg_task(SendMsgDone done)
{
	auto *task = this->create_rpc_client_task("/State/SendMsg", std::move(done));

	if (!this->params.caller.empty())
		task->get_req()->set_caller_name(this->params.caller);

	return task;
}

inline TRPCHttpClient::TRPCHttpClient(const char *host, unsigned short port):
	srpc::TRPCHttpClient("State")
{
	struct srpc::RPCClientParams params = srpc::RPC_CLIENT_PARAMS_DEFAULT;
	
	params.host = host;
	params.port = port;
	this->srpc::TRPCHttpClient::init(&params);
}

inline TRPCHttpClient::TRPCHttpClient(const struct srpc::RPCClientParams *params):
	srpc::TRPCHttpClient("State")
{
	const struct srpc::RPCClientParams *temp = params;
	struct srpc::RPCClientParams temp_params;
	
	this->srpc::TRPCHttpClient::init(temp);
}

inline void TRPCHttpClient::CancelConn(const StateRequest *req, CancelConnDone done)
{
	auto *task = this->create_rpc_client_task("CancelConn", std::move(done));

	if (this->params.callee_timeout >= 0)
		task->get_req()->set_callee_timeout(this->params.callee_timeout);
	if (!this->params.caller.empty())
		task->get_req()->set_caller_name(this->params.caller);
	task->serialize_input(req);
	task->start();
}

inline void TRPCHttpClient::CancelConn(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx)
{
	auto res = this->async_CancelConn(req).get();

	if (resp && res.second.success)
		*resp = std::move(res.first);

	if (sync_ctx)
		*sync_ctx = std::move(res.second);
}

inline WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> TRPCHttpClient::async_CancelConn(const StateRequest *req)
{
	using RESULT = std::pair<StateResponse, srpc::RPCSyncContext>;
	auto *pr = new WFPromise<RESULT>();
	auto fr = pr->get_future();
	auto *task = this->create_rpc_client_task<StateResponse>("CancelConn", srpc::RPCAsyncFutureCallback<StateResponse>);

	if (this->params.callee_timeout >= 0)
		task->get_req()->set_callee_timeout(this->params.callee_timeout);
	if (!this->params.caller.empty())
		task->get_req()->set_caller_name(this->params.caller);
	task->serialize_input(req);
	task->user_data = pr;
	task->start();
	return fr;
}

inline void TRPCHttpClient::SendMsg(const StateRequest *req, SendMsgDone done)
{
	auto *task = this->create_rpc_client_task("SendMsg", std::move(done));

	if (this->params.callee_timeout >= 0)
		task->get_req()->set_callee_timeout(this->params.callee_timeout);
	if (!this->params.caller.empty())
		task->get_req()->set_caller_name(this->params.caller);
	task->serialize_input(req);
	task->start();
}

inline void TRPCHttpClient::SendMsg(const StateRequest *req, StateResponse *resp, srpc::RPCSyncContext *sync_ctx)
{
	auto res = this->async_SendMsg(req).get();

	if (resp && res.second.success)
		*resp = std::move(res.first);

	if (sync_ctx)
		*sync_ctx = std::move(res.second);
}

inline WFFuture<std::pair<StateResponse, srpc::RPCSyncContext>> TRPCHttpClient::async_SendMsg(const StateRequest *req)
{
	using RESULT = std::pair<StateResponse, srpc::RPCSyncContext>;
	auto *pr = new WFPromise<RESULT>();
	auto fr = pr->get_future();
	auto *task = this->create_rpc_client_task<StateResponse>("SendMsg", srpc::RPCAsyncFutureCallback<StateResponse>);

	if (this->params.callee_timeout >= 0)
		task->get_req()->set_callee_timeout(this->params.callee_timeout);
	if (!this->params.caller.empty())
		task->get_req()->set_caller_name(this->params.caller);
	task->serialize_input(req);
	task->user_data = pr;
	task->start();
	return fr;
}

inline srpc::TRPCHttpClientTask *TRPCHttpClient::create_CancelConn_task(CancelConnDone done)
{
	auto *task = this->create_rpc_client_task("CancelConn", std::move(done));

	if (!this->params.caller.empty())
		task->get_req()->set_caller_name(this->params.caller);

	return task;
}

inline srpc::TRPCHttpClientTask *TRPCHttpClient::create_SendMsg_task(SendMsgDone done)
{
	auto *task = this->create_rpc_client_task("SendMsg", std::move(done));

	if (!this->params.caller.empty())
		task->get_req()->set_caller_name(this->params.caller);

	return task;
}

} // end namespace State

