#pragma once
#include <tuple>

namespace water {
	namespace calculus {
		template<class T>
		class range {
		public:
			range(T min, T max) : m_min{ min }, m_max{ max } {}
			T min() const {
				return m_min;
			}
			T max() const {
				return m_max;
			}
		private:
			T m_min;
			T m_max;
		};
		template<class Range>
		concept range_c = requires (Range r) {
			r.min();
			r.max();
		};
		template<size_t SAMPLE_COUNT>
		auto integrate_by_sample(auto&& f, range_c auto&& range) {
			auto sample_width = (range.max() - range.min()) / SAMPLE_COUNT;
			auto begin = range.min() + sample_width / 2;
			auto last = range.max() - sample_width / 2;
			
			auto sample = begin;
			auto sum = f(sample);
			while (sample += sample_width, sample <= last) {
				sum += f(sample);
			}

			return sum / SAMPLE_COUNT;
		}
		template<class Area>
		concept area_c = requires (Area a) {
			a.start_pos();
			a.width();
			a.height();
		};
		template<class T>
		class area {
		public:
			area(T x, T y, T w, T h) : m_x{ x }, m_y{ y }, m_w{ w }, m_h{ h } {}
			auto start_pos() const {
				return std::pair<T, T>{m_x, m_y};
			}
			auto width() const {
				return m_w;
			}
			auto height() const {
				return m_h;
			}
			auto set_x(T x) {
				m_x = x;
			}
			auto set_y(T y) {
				m_y = y;
			}
			auto set_width(T width) {
				m_w = width;
			}
			auto set_height(T height) {
				m_h = height;
			}
		private:
			T m_x;
			T m_y;
			T m_w;
			T m_h;
		};
		template<size_t SAMPLE_COUNT>
		auto integrate_by_sample(auto&& f, area_c auto&& area) {
			if (SAMPLE_COUNT == 1) {
				auto [x, y] = area.start_pos();
				x += area.width() / 2;
				y += area.height() / 2;
				return f(x, y) * area.width() * area.height();
			}
			else if (area.width() > area.height()) {
				auto [x, y] = area.start_pos();
				auto left_area = area;
				left_area.set_width(area.width() / 2);
				auto right_area = area;
				right_area.set_x(x + area.width() / 2);
				right_area.set_width(area.width() / 2);
				return integrate_by_sample<(SAMPLE_COUNT + 1) / 2>(f, left_area) + integrate_by_sample<SAMPLE_COUNT / 2>(f, right_area);
			}
			else {
				auto [x, y] = area.start_pos();
				auto top_area = area;
				top_area.set_height(area.height() / 2);
				auto down_area = area;
				down_area.set_y(y + area.height() / 2);
				down_area.set_height(area.height() / 2);
				return integrate_by_sample<(SAMPLE_COUNT + 1) / 2>(f, top_area) + integrate_by_sample<SAMPLE_COUNT / 2>(f, down_area);
			}
		}
	}
}
