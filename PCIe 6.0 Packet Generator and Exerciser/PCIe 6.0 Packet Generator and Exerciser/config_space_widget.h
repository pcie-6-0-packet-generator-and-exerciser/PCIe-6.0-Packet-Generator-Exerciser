#pragma once
#include <QtWidgets/QFrame>
#include "type1_config_space/type1_config.h"


namespace Ui {
	class ConfigSpaceWidget : public QFrame
	{
		Q_OBJECT
		public:
			explicit ConfigSpaceWidget(Type1Config* type1space, QWidget* parent = nullptr);
			~ConfigSpaceWidget();
		

	};
}