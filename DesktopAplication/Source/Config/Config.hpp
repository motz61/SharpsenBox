﻿#pragma once
#include <QObject>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QNetworkAccessManager>
#include "IComponent.hpp"
#include "Game.hpp"
#include <filesystem>
#include <vector>


namespace cf {
	class Config : public bc::IQmlComponent<Config> {
		Q_OBJECT
	public:
		Config();
		virtual ~Config();

		// implementation IQmlObject
		void update() override {};
		void init() override;
		std::string getName() override;

		// interface 
		void insertGame(Game& game) { games_.insert({ game.id,  game }); };
		bool gameExists(int id);
		Game& getGame(int id);
		std::string gamePageDir(int id);
		QString& getVer() { return version_; }
		void setVer(QString ver) { version_ = ver; }

		std::filesystem::path& getDownloadDir() { return downloadDir_; }
		std::filesystem::path getConfigJson() { return config_ / configJson_; }
		std::filesystem::path getConfigJsonFileName() { return configJson_; }
		std::filesystem::path getLauncherAppInfoUrl() { return LauncherAppInfo; }
		std::filesystem::path getGameInfoRepository() { return gameInfoRepo_; }

		//QMl invoklabes
		Q_INVOKABLE bool installed(int id) const;
		Q_INVOKABLE QString gameInfoDir(int id);
		Q_INVOKABLE QUrl defaultInstallDir();
		Q_INVOKABLE void setDownloadSpeed(qint32 dp) { downloadSpeed_ = dp; }
		Q_INVOKABLE qint32 getDownloadSpeed() { return downloadSpeed_; }
		Q_INVOKABLE void setGameAutoCheck(int id, bool val) { getGame(id).autoCheck = val; }
		Q_INVOKABLE bool getGameAutoCheck(int id) { bool v = getGame(id).autoCheck;	return v; }
		Q_INVOKABLE QString getGameName(int id) { return getGame(id).name; }
		Q_INVOKABLE QString  getConfigJsonUrl() { return ""; } //!!!!!!!!!
		Q_INVOKABLE int getGameId(); // get game id for game choser
		Q_INVOKABLE QString getGamePresentationUrl(int id); // get game id for game choser
		Q_INVOKABLE QString getPresentationFile(int id);
		Q_INVOKABLE int getDefaultGameId();
		Q_INVOKABLE QString getCurrentDirectory();


	private:
		void readGames();
		Game readGameInfo(const QJsonObject& value);
		void writeGames();
		QJsonObject parseGameInfo(const Game& game);
	private:
		std::filesystem::path config_ = "../Config";
		std::filesystem::path downloadDir_ = "../Download";
		std::filesystem::path configJson_ = "LaunchBoxInfo.json";
		std::filesystem::path gamesFileName_ = "Games.json";

		std::unordered_map<int, Game> games_;

		QString version_;
		qint32 downloadSpeed_;
		std::filesystem::path gameInfoRepo_;
		std::filesystem::path LauncherAppInfo;

		//for gamebar
		int maxGameBarLen_ = 10;
		std::vector<int> sortedId_;
	};
}
