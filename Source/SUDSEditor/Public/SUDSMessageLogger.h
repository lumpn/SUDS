﻿#pragma once

struct SUDSEDITOR_API FSUDSMessageLogger
{
protected:
	TArray<TSharedRef<FTokenizedMessage>> ErrorMessages;

	bool bWriteToMessageLog = true;
public:
	FSUDSMessageLogger() {}
	FSUDSMessageLogger(bool bWriteToMsg) : bWriteToMessageLog(bWriteToMsg) {}
	~FSUDSMessageLogger();

	void SetWriteToMessageLog(bool bWrite) { bWriteToMessageLog = bWrite; }
	bool HasErrors() const;
	int NumErrors() const;
	
	void AddMessage(EMessageSeverity::Type Severity, const FText& Text);
	template <typename FmtType, typename... Types>
	FORCEINLINE void Logf(ELogVerbosity::Type Verbosity, const FmtType& Fmt, Types... Args)
	{
		EMessageSeverity::Type Sev = EMessageSeverity::Info;
		switch(Verbosity)
		{
		case ELogVerbosity::Fatal:
		case ELogVerbosity::Error:
			Sev = EMessageSeverity::Error;
			break;
		case ELogVerbosity::Warning:
			Sev = EMessageSeverity::Warning;
			break;
		default: ;
		}
		AddMessage(Sev, FText::FromString(FString::Printf(Fmt, Args...)));
	}
};
