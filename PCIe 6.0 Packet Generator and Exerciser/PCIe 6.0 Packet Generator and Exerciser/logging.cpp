#include "logging.h"

void initLogging()
{
	logging::add_common_attributes();

	logging::core::get()->add_global_attribute(
		"ThreadID",
		attrs::current_thread_id());

	logging::add_file_log
	(
		keywords::file_name = "sample_%N.log",                                        /*< file name pattern >*/
		keywords::rotation_size = 10 * 1024 * 1024,                                   /*< rotate files every 10 MiB... >*/
		keywords::format =
		(
			expr::stream
			<< expr::attr< unsigned int >("ThreadID")
			<< expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
			<< ": <" << logging::trivial::severity
			<< "> " << expr::smessage
			)
	);

	logging::core::get()->set_filter
	(
		logging::trivial::severity >= logging::trivial::trace
	);
}