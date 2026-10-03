//  entityStates.cpp (WithLand Core)
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

#include <withland/core/components/entityStates.hpp>

namespace withland {
    namespace components {
        const std::vector<std::string> male_names_colonist = {
            "Arthur", "Alexander", "Benjamin", "Charles", "Daniel", 
            "Edward", "Edward", "Ethan", "George", "Henry", 
            "Jack", "James", "Liam", "Matthew", "Oliver", 
            "Richard", "Robert", "Samuel", "Thomas", "William"
        };

        const std::vector<std::string> female_names_colonist = {
            "Alice", "Amelia", "Beatrice", "Charlotte", "Diana", 
            "Eleanor", "Elizabeth", "Emma", "Evelyn", "Grace", 
            "Isabella", "Lily", "Lucy", "Margaret", "Olivia", 
            "Sophia", "Rose", "Victoria", "Victoria", "Sophia"
        };
    }
}