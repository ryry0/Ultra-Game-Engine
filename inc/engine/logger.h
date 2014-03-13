#ifndef LOGGER_H_
#define LOGGER_H_
#include <sstream>
#include <cstdio>
#include <ctime>

/*
 * Description:
 *  This is a logger class. All you need to do to use it is to include it in
 *  your file, and call LOG(severity) << "Error Message"; or
 *                      Logger.Get(severity) << "Error Message";
 *  It is typesafe, thread-safe and portable.
 *  Uses an std::ostringstream to accumulate the logged data. Based on
 *  code from the OpenXCom Project.
 *
 * Functions:
 *  Destructor: Writes all log information to standard error.
 *  Get: Returns the string stream operator. It is used as the interface to
 *    Log errors.
 *  ReportingLevel: Read or set the reporting level.
 *  LogFile: Read or set the log file.
 */

/*
 * Use the following macro to ensure that there is no performance hit when
 * not logging. Setting the reporting level to LOG_INFO will log every
 * error message down. Setting it to LOG_FATAL will only log fatal errors.
 */
#define LOG(level) \
  if (level > Logger::ReportingLevel()) ; \
  else Logger().Get(level)

inline std::string TimeNow();
enum LogSeverityLevel
{
  LOG_FATAL,  //Crash-Level errors.
  LOG_ERROR,  //Serious, but recoverable errors.
  LOG_WARNING,//Something happened that may cause trouble
  LOG_DEBUG,  //Normal Debug information. (logical errors)
  LOG_INFO,   //Useful information to know. (API version, capabilities, etc)
};

constexpr LogSeverityLevel REPORTING_LEVEL = LOG_DEBUG;
const std::string LOG_FILE_NAME = "log.txt";

class Logger
{
  public:
            Logger  ();
    virtual ~Logger ();
            std::ostringstream& Get(LogSeverityLevel level = LOG_INFO);
    static  LogSeverityLevel&   ReportingLevel();
    static  std::string&        LogFile       ();
    static  std::string         ToString      (LogSeverityLevel level);

  protected:
    std::ostringstream output_stream_;
  private:
    Logger(const Logger&);
    Logger& operator =(const Logger&);
    LogSeverityLevel message_level_;
};

inline Logger::Logger()
{
}

inline std::ostringstream& Logger::Get(LogSeverityLevel level)
{
  output_stream_ << "[" << ToString(level) << "]" << "\t";
  return output_stream_;
}

/*
 * Thread safe, logs output to a file when the object is destroyed.
 * Only logs if the message to log is greater than or equal to the
 * level to report.
 */
inline Logger::~Logger()
{
    output_stream_ << std::endl;
    if (ReportingLevel() == LOG_INFO) //write to stderr only when LOG_INFO
    {
      fprintf(stderr, "%s", output_stream_.str().c_str());
      fflush(stderr);
    }
    std::ostringstream stream_buffer;
    stream_buffer << "[" << TimeNow() << "]" << "\t" << output_stream_.str();
    FILE *log_file = fopen(LogFile().c_str(), "a");
    fprintf(log_file, "%s", stream_buffer.str().c_str());
    fflush(log_file);
    fclose(log_file);
}

/*
 * Returns the reporting level of the logger, and you can change it.
 */
inline LogSeverityLevel& Logger::ReportingLevel()
{
  static LogSeverityLevel reporting_level = REPORTING_LEVEL;
  return reporting_level;
}

/*
 * Returns the name of the log file, and you can change it.
 */
inline std::string& Logger::LogFile()
{
  static std::string log_file = LOG_FILE_NAME;
  return log_file;
}

/*
 * Parses the log severity level and returns it in string form.
 */
inline std::string Logger::ToString(LogSeverityLevel level)
{
  static const char* const severity_levels[] = {"FATAL", "ERROR", "WARN",
    "DEBUG","INFO"};
  return severity_levels[level];
}

/*
 * Grabs the time of logging, and returns a string containing that info.
 */
inline std::string TimeNow()
{
  const int BUFFER_LENGTH = 25, RESULT_LENGTH = 80;
  char buffer[BUFFER_LENGTH];
  time_t raw_time;
  struct tm *time_info;

  time(&raw_time);
  time_info = localtime(&raw_time);
  strftime(buffer, BUFFER_LENGTH, "%m/%d/%Y %H:%M:%S", time_info);

  char result[RESULT_LENGTH] = {0};
  sprintf(result, "%s", buffer);
  return result;
}

#endif
