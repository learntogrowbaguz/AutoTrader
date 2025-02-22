#include "DBWrapper.h"
//must put "#include <winsock2.h>" before #include "mysqlwrapper.h". otherwise will cause compile error
#ifdef WIN32
#include <winsock2.h>
#endif
#include "mysqlwrapper.h"
#include "Config.h"
#include "spdlog/spdlog.h"
#include "crossplatform.h"

std::map<std::string, bool> DBUtils::m_dict;

int DBUtils::CreateTickTableIfNotExists(const std::string& dbname, const std::string& tableName){

	if (DBUtils::m_dict.find(tableName) != m_dict.end()){
		return 0;
	}
	else
	{
		DBUtils::m_dict[tableName] = true;
		const char* sqltempl = "CREATE TABLE IF NOT EXISTS `%s`.`%s` (\
			`id` INT NOT NULL AUTO_INCREMENT, \
			`Date` DATE NULL, \
			`InstrumentID` VARCHAR(32) NULL, \
			`ExchangeID` VARCHAR(16) NULL, \
			`ExchangeInstID` VARCHAR(32) NULL, \
			`LastPrice` DOUBLE NULL, \
			`PreSettlementPrice` DOUBLE NULL, \
			`PreClosePrice` DOUBLE NULL, \
			`PreOpenInterest` DOUBLE NULL, \
			`OpenPrice` DOUBLE NULL, \
			`HighestPrice` DOUBLE NULL, \
			`LowestPrice` DOUBLE NULL, \
			`Volume` DOUBLE NULL, \
			`Turnover` DOUBLE NULL, \
			`OpenInterest` DOUBLE NULL, \
			`ClosePrice` DOUBLE NULL, \
			`SettlementPrice` DOUBLE NULL, \
			`UpperLimitPrice` DOUBLE NULL, \
			`LowerLimitPrice` DOUBLE NULL, \
			`PreDelta` DOUBLE NULL, \
			`CurrDelta` DOUBLE NULL, \
			`UpdateTime` TIME NULL, \
			`UpdateMillisec` INT NULL, \
			`BidPrice1` DOUBLE NULL, \
			`BidVolume1` DOUBLE NULL, \
			`AskPrice1` DOUBLE NULL, \
			`AskVolume1` DOUBLE NULL, \
			`BidPrice2` DOUBLE NULL, \
			`BidVolume2` DOUBLE NULL, \
			`AskPrice2` DOUBLE NULL, \
			`AskVolume2` DOUBLE NULL, \
			`BidPrice3` DOUBLE NULL, \
			`BidVolume3` DOUBLE NULL, \
			`AskPrice3` DOUBLE NULL, \
			`AskVolume3` DOUBLE NULL, \
			`BidPrice4` DOUBLE NULL, \
			`BidVolume4` DOUBLE NULL, \
			`AskPrice4` DOUBLE NULL, \
			`AskVolume4` DOUBLE NULL, \
			`BidPrice5` DOUBLE NULL, \
			`BidVolume5` DOUBLE NULL, \
			`AskPrice5` DOUBLE NULL, \
			`AskVolume5` DOUBLE NULL, \
			`AveragePrice` DOUBLE NULL, \
			`ActionDay` DATE NULL, \
			`uuid` BIGINT NULL, \
			PRIMARY KEY(`id`));";
		char sqlbuf[2046];
		SPRINTF(sqlbuf, sqltempl, dbname.c_str(), tableName.c_str());
		DBWrapper db;
		return db.ExecuteNoResult(sqlbuf);
	}
}

DBWrapper::DBWrapper()
	:m_MysqlImpl(new mysql_db())
{
	if (-1 == m_MysqlImpl->mysql_open(Config::Instance()->DBHost().c_str() \
		, Config::Instance()->DBUser().c_str() \
		, Config::Instance()->DBPassword().c_str() \
		, Config::Instance()->DBName().c_str() \
		, Config::Instance()->DBPort()))
	{
		//SYNC_PRINT << m_MysqlImpl->mysql_lasterror();
	}
		
	//ExecuteNoResult("ExecuteNoResult")
}

DBWrapper::~DBWrapper()
{
}


int DBWrapper::ExecuteNoResult(const std::string& sql){
	int ret = m_MysqlImpl->mysql_noResult_query(sql.c_str());
	//if (-1 == ret)
		//SYNC_PRINT << m_MysqlImpl->mysql_lasterror();
	return ret;
}

int DBWrapper::Query(const std::string& sql, std::map<int, std::vector<std::string>> & map_results)
{
	int ret = m_MysqlImpl->mysql_select_query(sql.c_str(), map_results);
	//if (-1 == ret)
		//SYNC_PRINT << m_MysqlImpl->mysql_lasterror();
	return ret;
}
