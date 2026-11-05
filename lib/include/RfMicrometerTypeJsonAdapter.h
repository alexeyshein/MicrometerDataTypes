#pragma once

#include <json.hpp>

#include "Point2d.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "SegmentLine.h"
#include "StraightLine.h"
#include "Polyline.h"
#include "Contour.h"
#include "Profile.h"
// #include "RotatedRect.h"   // добавьте, когда пришлёте объявление

namespace nlohmann
{

	// Point2d<T> -> {"x": ..., "y": ...}
	template<typename T>
	struct adl_serializer<rf::Point2d<T>>
	{
		template<typename BasicJsonType>
		static void to_json(BasicJsonType& j, const rf::Point2d<T>& p)
		{
			j = BasicJsonType{ { "x", p.x },{ "y", p.y } };
		}

		template<typename BasicJsonType>
		static void from_json(const BasicJsonType& j, rf::Point2d<T>& p)
		{
			p = rf::Point2d<T>(j.at("x").template get<T>(), j.at("y").template get<T>());
		}
	};

	// Rect -> {"x", "y", "width", "height"}
	template<>
	struct adl_serializer<rf::Rect>
	{
		template<typename BasicJsonType>
		static void to_json(BasicJsonType& j, const rf::Rect& r)
		{
			const auto tl = r.PointTl();
			j = BasicJsonType{
				{ "x",      tl.x },
				{ "y",      tl.y },
				{ "width",  r.Width() },
				{ "height", r.Height() }
			};
		}

		template<typename BasicJsonType>
		static void from_json(const BasicJsonType& j, rf::Rect& r)
		{
			const rf::Point2d<double> tl(j.at("x").template get<double>(), j.at("y").template get<double>());
			r = rf::Rect(tl, j.at("width").template get<double>(), j.at("height").template get<double>());
		}
	};

	// RotatedRect -> {"center": {x, y}, "width": ..., "height": ..., "angle": ...}
	template<>
	struct adl_serializer<rf::RotatedRect>
	{
		template<typename BasicJsonType>
		static void to_json(BasicJsonType& j, const rf::RotatedRect& r)
		{
			j = BasicJsonType{
				{ "center", r.Center() },   // Point2d уже сериализуется адаптером выше
				{ "width",  r.Width() },
				{ "height", r.Height() },
				{ "angle",  r.Angle() }
			};
		}

		template<typename BasicJsonType>
		static void from_json(const BasicJsonType& j, rf::RotatedRect& r)
		{
			r = rf::RotatedRect(j.at("center").template get<rf::Point2d<double>>(),
				j.at("width").template get<double>(),
				j.at("height").template get<double>(),
				j.at("angle").template get<double>());
		}
	};

	// SegmentLine -> {"point1": {x, y}, "point2": {x, y}}
	template<>
	struct adl_serializer<rf::SegmentLine>
	{
		template<typename BasicJsonType>
		static void to_json(BasicJsonType& j, const rf::SegmentLine& s)
		{
			j = BasicJsonType{
				{ "point1", s.Point1() },
				{ "point2", s.Point2() }
			};
		}

		template<typename BasicJsonType>
		static void from_json(const BasicJsonType& j, rf::SegmentLine& s)
		{
			s = rf::SegmentLine(j.at("point1").template get<rf::Point2d<double>>(),
				j.at("point2").template get<rf::Point2d<double>>());
		}
	};

	// StraightLine -> {"a": ..., "b": ..., "c": ...}  (прямая a*x + b*y + c = 0)
	template<>
	struct adl_serializer<rf::StraightLine>
	{
		template<typename BasicJsonType>
		static void to_json(BasicJsonType& j, const rf::StraightLine& l)
		{
			j = BasicJsonType{
				{ "a", l.A() },
				{ "b", l.B() },
				{ "c", l.C() }
			};
		}

		template<typename BasicJsonType>
		static void from_json(const BasicJsonType& j, rf::StraightLine& l)
		{
			l = rf::StraightLine(j.at("a").template get<double>(),
				j.at("b").template get<double>(),
				j.at("c").template get<double>());
		}
	};

	// PolyLine -> {"id": ..., "points": [{x, y}, ...]}
	template<>
	struct adl_serializer<rf::PolyLine>
	{
		template<typename BasicJsonType>
		static void to_json(BasicJsonType& j, const rf::PolyLine& pl)
		{
			j = BasicJsonType{
				{ "id",     pl.Id() },
				{ "points", pl.PolyLineConstRef() }
			};
		}

		template<typename BasicJsonType>
		static void from_json(const BasicJsonType& j, rf::PolyLine& pl)
		{
			pl.Set(j.at("id").template get<uint64_t>(),
				j.at("points").template get<std::vector<rf::Point2d<double>>>());
		}
	};

	// Contour -> {"type": 0|1, "points": [{x, y}, ...]}
	// Формат совпадает с ProfileToJson.
	template<>
	struct adl_serializer<rf::Contour>
	{
		template<typename BasicJsonType>
		static void to_json(BasicJsonType& j, const rf::Contour& c)
		{
			j = BasicJsonType{
				{ "type",   c.GetContourType() },
				{ "points", c.PointsConstRef() }
			};
		}
		template<typename BasicJsonType>
		static void from_json(const BasicJsonType& j, rf::Contour& c)
		{
			c = rf::Contour(0,
				j.at("points").template get<std::vector<rf::Point2d<double>>>(),
				static_cast<rf::ContourType>(j.at("type").template get<int>()));
		}
	};

	// Profile -> {"contours": [...], "hierarchy": [...]}
	// Формат совпадает с ProfileToJson.
	template<>
	struct adl_serializer<rf::Profile>
	{
		template<typename BasicJsonType>
		static void to_json(BasicJsonType& j, const rf::Profile& p)
		{
			j = BasicJsonType{
				{ "contours",  p.ContoursConstRef() },
				{ "hierarchy", p.HierarchyConstRef() }
			};
		}
		
		template<typename BasicJsonType>
		static void from_json(const BasicJsonType& j, rf::Profile& p)
		{
			p = rf::Profile(0, 0,
				j.at("contours").template get<std::vector<rf::Contour>>(),
				j.at("hierarchy").template get<std::vector<int>>());
		}
	};

} // namespace nlohmann