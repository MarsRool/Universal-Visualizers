#pragma once

namespace MR
{
	namespace Helpers
	{
		class Array
		{
		private:
			double* Ptr;
			int size;
		public:
			Array();
			Array(double* Ptr_i, int size_i);
			Array(const Array & arrayToCopy);
			~Array();

			double & at(int k, bool isOk);//возвращает

			double operator[] (int k); // перегруженная операция взятия индекса
		};
	}
}