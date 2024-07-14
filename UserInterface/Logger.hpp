#pragma once

#include "ThreadSafeQueue.hpp"

struct Message
{
	std::string msg;
	int expirationTime; // >=0: frames, -1: permanent
};

class Logger
{
public:
	static Logger& getInstance() 
	{
		static Logger instance;
		return instance;
	}

	void LogMsg(const std::string & msg, const int & expirationTime)
	{
		m_msgQueue.push(Message{msg, expirationTime});
	}

	Message ReadLog()
	{
		return m_msgQueue.pop();
	}

	bool NoMessage()
	{
		return m_msgQueue.empty();
	}

private:
	Logger() = default;
	~Logger() = default;
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	ThreadSafeQueue<Message> m_msgQueue;
};

#define LOG_MSG(msg, expirationTime) Logger::getInstance().LogMsg(msg,expirationTime)