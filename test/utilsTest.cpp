// Copyright 2018 Alessio Sclocco <alessio@sclocco.eu>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <utils.hpp>
#include <gtest/gtest.h>

TEST(ReplaceTest, PlaceholderInString) {
  EXPECT_EQ(std::string("Hello World!"), *(isa::utils::replace(new std::string("Hello <%NAME%>!"), "<%NAME%>", "World")));
  EXPECT_EQ(std::string("Hello WorldWorldWorld!"), *(isa::utils::replace(new std::string("Hello <%NAME%><%NAME%><%NAME%>!"), "<%NAME%>", "World")));
  EXPECT_EQ(std::string("Please to meet you John."), *(isa::utils::replace(new std::string("<%SENTENCE%>."), "<%SENTENCE%>", "Please to meet you John", true)));
}

TEST(ReplaceTest, PlaceholderNotInString) {
  EXPECT_EQ(std::string("Hello again, World!"), *(isa::utils::replace(new std::string("Hello again, World!"), "<%PLACEHOLDER%>", "John")));
  EXPECT_EQ(std::string("<%SENTENCE%>."), *(isa::utils::replace(new std::string("<%SENTENCE%>."), "<%PLACEHOLDER%>", "Please to meet you Mike", true)));
}

TEST(ReplaceTest, EraseString) {
  EXPECT_EQ(std::string(""), *(isa::utils::replace(new std::string("Hello World!"), "Hello World!", "")));
  EXPECT_EQ(std::string(""), *(isa::utils::replace(new std::string("Hello World!"), "Hello World!", "", true)));
}

TEST(SameTest, SameValue) {
  float singlePrecision = 932.728292f;
  float doublePrecision = 932.728636126;

  EXPECT_TRUE(isa::utils::same(singlePrecision, singlePrecision)) << "Values: " << singlePrecision << " " << singlePrecision;
  EXPECT_TRUE(isa::utils::same(doublePrecision, doublePrecision, 1.0e-03)) << "Values: " << doublePrecision << " " << singlePrecision;
  EXPECT_TRUE(isa::utils::same(doublePrecision, doublePrecision)) << "Values: " << doublePrecision << " " << doublePrecision;
  EXPECT_TRUE(isa::utils::same(doublePrecision, doublePrecision, 1.0e-09)) << "Values: " << doublePrecision << " " << doublePrecision;
}

TEST(SameTest, DifferentValue) {
  float singlePrecision = 932.728292f;
  float doublePrecision = 932.728636126;

  EXPECT_FALSE(isa::utils::same(singlePrecision, doublePrecision)) << "Values: " << singlePrecision << " " << doublePrecision;
  EXPECT_FALSE(isa::utils::same(doublePrecision, singlePrecision)) << "Values: " << doublePrecision << " " << singlePrecision;
  EXPECT_TRUE(isa::utils::same(singlePrecision, doublePrecision, 1.0e-03)) << "Values: " << singlePrecision << " " << doublePrecision;
  EXPECT_TRUE(isa::utils::same(doublePrecision, singlePrecision, 1.0e-03)) << "Values: " << doublePrecision << " " << singlePrecision;
  EXPECT_FALSE(isa::utils::same(singlePrecision, doublePrecision, 1.0e-04)) << "Values: " << singlePrecision << " " << doublePrecision;
  EXPECT_FALSE(isa::utils::same(doublePrecision, singlePrecision, 1.0e-04)) << "Values: " << doublePrecision << " " << singlePrecision;
}

TEST(CastToTypeTest, TypeDifferent) {
  int integer;
  float singlePrecision;
  double doublePrecision;
  std::string stringNumber;

  singlePrecision = 12.379238f;
  integer = isa::utils::castToType<float, int>(singlePrecision);
  EXPECT_EQ(12, integer);
  integer = 42;
  doublePrecision = isa::utils::castToType<int, double>(integer);
  EXPECT_EQ(42.0, doublePrecision);
  stringNumber = "1923";
  integer = isa::utils::castToType<std::string, int>(stringNumber);
  EXPECT_EQ(1923, integer);
  stringNumber = "92.732";
  singlePrecision = isa::utils::castToType<std::string, float>(stringNumber);
  EXPECT_EQ(92.732f, singlePrecision);
  doublePrecision = 82372.8;
  stringNumber = isa::utils::castToType<double, std::string>(doublePrecision);
  EXPECT_EQ("82372.8", stringNumber);
}

TEST(CastToTypeTest, TypeEqual) {
  int integerOne, integerTwo;
  float singlePrecisionOne, singlePrecisionTwo;
  double doublePrecisionOne, doublePrecisionTwo;

  integerOne = 42;
  integerTwo = isa::utils::castToType<int, int>(integerOne);
  EXPECT_EQ(integerOne, integerTwo);
  singlePrecisionOne = 12.379f;
  singlePrecisionTwo = isa::utils::castToType<float, float>(singlePrecisionOne);
  EXPECT_TRUE(isa::utils::same(singlePrecisionOne, singlePrecisionTwo, 1.0e-03)) << "Values: " << singlePrecisionOne << " " << singlePrecisionTwo;
  doublePrecisionOne = 928.728;
  doublePrecisionTwo = isa::utils::castToType<double, double>(doublePrecisionOne);
  EXPECT_TRUE(isa::utils::same(doublePrecisionOne, doublePrecisionTwo, 1.0e-03)) << "Values: " << doublePrecisionOne << " " << doublePrecisionTwo;
}

TEST(PadTest, NumberIsPadded) {
  EXPECT_EQ(10, isa::utils::pad(7, 5));
  EXPECT_EQ(83, isa::utils::pad(12, 83));
}

TEST(PadTest, NumberIsNotPadded) {
  EXPECT_EQ(92, isa::utils::pad(92, 92));
  EXPECT_EQ(92, isa::utils::pad(92, 2));
  EXPECT_EQ(92, isa::utils::pad(92, 1));
  EXPECT_EQ(28, isa::utils::pad(28, 7));
}

TEST(TeraTest, TeraConversion) {
  EXPECT_TRUE(isa::utils::same(123.456789123, isa::utils::tera(123456789123456), 1.0e-09)) << "Values: " << 123.456789123 << " " << isa::utils::tera(123456789123456);
  EXPECT_TRUE(isa::utils::same(0.123456789, isa::utils::tera(123456789123), 1.0e-09)) << "Values: " << 0.123456789 << " " << isa::utils::tera(123456789123);
  EXPECT_TRUE(isa::utils::same(0.000123456, isa::utils::tera(123456789), 1.0e-09)) << "Values: " << 0.000123456 << " " << isa::utils::tera(123456789);
  EXPECT_TRUE(isa::utils::same(0.000000123, isa::utils::tera(123456), 1.0e-09)) << "Values: " << 0.000000123 << " " << isa::utils::tera(123456);
}

TEST(GigaTest, GigaConversion) {
  EXPECT_TRUE(isa::utils::same(123.789123456, isa::utils::giga(123789123456), 1.0e-09)) << "Values: " << 123.789123456 << " " << isa::utils::giga(123789123456);
  EXPECT_TRUE(isa::utils::same(0.123456789, isa::utils::giga(123456789), 1.0e-09)) << "Values: " << 0.123456789 << " " << isa::utils::giga(123456789);
  EXPECT_TRUE(isa::utils::same(0.000123456, isa::utils::giga(123456), 1.0e-09)) << "Values: " << 0.000123456 << " " << isa::utils::giga(123456);
  EXPECT_TRUE(isa::utils::same(0.000000123, isa::utils::giga(123), 1.0e-09)) << "Values: " << 0.000000123 << " " << isa::utils::giga(123);
}

TEST(MegaTest, MegaConversion) {
  EXPECT_TRUE(isa::utils::same(123789.123456, isa::utils::mega(123789123456))) << "Values: " << 123789.123456 << " " << isa::utils::mega(123789123456);
  EXPECT_TRUE(isa::utils::same(123.456789, isa::utils::mega(123456789))) << "Values: " << 123.456789 << " " << isa::utils::mega(123456789);
  EXPECT_TRUE(isa::utils::same(0.123456, isa::utils::mega(123456))) << "Values: " << 0.123456 << " " << isa::utils::mega(123456);
  EXPECT_TRUE(isa::utils::same(0.000123, isa::utils::mega(123))) << "Values: " << 0.000123 << " " << isa::utils::mega(123);
}

TEST(KiloTest, KiloConversion) {
  EXPECT_TRUE(isa::utils::same(123789123.456, isa::utils::kilo(123789123456), 1.0e-03)) << "Values: " << 123789123.456 << " " << isa::utils::kilo(123789123456);
  EXPECT_TRUE(isa::utils::same(123456.789, isa::utils::kilo(123456789), 1.0e-03)) << "Values: " << 123456.789 << " " << isa::utils::kilo(123456789);
  EXPECT_TRUE(isa::utils::same(123.456, isa::utils::kilo(123456), 1.0e-03)) << "Values: " << 123.456 << " " << isa::utils::kilo(123456);
  EXPECT_TRUE(isa::utils::same(0.123, isa::utils::kilo(123), 1.0e-03)) << "Values: " << 0.123 << " " << isa::utils::kilo(123);
}
