#include "Header.h"

int main()
{
	
	Monitor_Current* monit_cur = new Monitor_Current;
	Monitor_Statistic* monit_stat = new Monitor_Statistic;
	Weather_Data weather_data;
	weather_data.Register_Observer(monit_cur);
	weather_data.Register_Observer(monit_stat);
	while (true)
	{
		cout << "\n++++++++++++++++++++++++";
		weather_data.Update();
		cout << "\nDo you want to see statistic info? y/n";
		char answer;
		cin >> answer;
		if (answer == 'y')
			monit_stat->Show_statistic();
		//cout << "\nPress 0 to exit or 1 to continue ";
		/*int press;
		cin >> press;
		if (!press)
			break;*/
	}


	if (monit_cur != nullptr)
		delete monit_cur;
	if (monit_stat != nullptr)
		delete monit_stat;

}