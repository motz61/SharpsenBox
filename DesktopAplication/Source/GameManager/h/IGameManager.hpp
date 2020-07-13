﻿#pragma once
#include <QObject>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QThread>
#include <QNetworkAccessManager>
#include "IComponent.hpp"

namespace gm {
	class GameUninstaller;
	struct IGameManager : bc::IQmlComponent {
	public:
		virtual ~IGameManager() {};
		IGameManager();

		// inferface
		virtual void lock() = 0;
		virtual void unLock() = 0;
		virtual void uninstall(bool dialogValue) = 0;

	signals:
		void lockChanged();
	};
}
