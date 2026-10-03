//  mainTest.cpp (WithLand Core)
//  WithLand — Behind every survivor is a choice: the land remembers those who stayed.
//
//  Copyright (C) 2026 Alexander Sharzhukov
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <withland/common/common.hpp>
#include <withland/core/colonist.hpp>
#include <cassert>

int main() {
    std::cout << "[test] start\n";
    withland::core::colonist col("Hero");
    assert(col.GetName() == "Hero");
    std::cout << col.GetName() << std::endl;
    std::cout << static_cast<int>(col.GetProfession()) << std::endl;
    std::cout << "[test] ALL OK\n";
    std::cin.get();
    return 0;
}