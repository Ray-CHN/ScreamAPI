#include "pch.h"
#include "eos-sdk/eos_connect.h"
#include "ScreamAPI.h"
#include "achievement_manager.h"

EOS_DECLARE_FUNC(void) EOS_Connect_Login(EOS_HConnect Handle, const EOS_Connect_LoginOptions* Options, void* ClientData, const EOS_Connect_OnLoginCallback CompletionDelegate){
	Logger::debug(__func__);

	static auto proxy = ScreamAPI::proxyFunction(&EOS_Connect_Login, __func__);
	auto container = new ScreamAPI::OriginalDataContainer(ClientData, CompletionDelegate);
	proxy(Handle, Options, container, [](const EOS_Connect_LoginCallbackInfo* Data){
		auto nonConstData = const_cast<EOS_Connect_LoginCallbackInfo*>(Data);
		ScreamAPI::proxyCallback(nonConstData, &nonConstData->ClientData, [&](){
			AchievementManager::init();
		});
	});
}

EOS_DECLARE_FUNC(EOS_ProductUserId) EOS_Connect_GetLoggedInUserByIndex(EOS_HConnect Handle, int32_t Index){
	Logger::debug(__func__);

	static auto proxy = ScreamAPI::proxyFunction(&EOS_Connect_GetLoggedInUserByIndex, __func__);
	return proxy(Handle, Index);
}