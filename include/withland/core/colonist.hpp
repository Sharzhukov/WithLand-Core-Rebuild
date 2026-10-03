//  colonist.hpp (WithLand Core)
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

#pragma once
#ifndef withland_colonist_hpp
#define withland_colonist_hpp

#include <withland/common/common.hpp>
#include <withland/core/components/entityStates.hpp>

namespace withland {
    
    namespace core {
        class colonist
        {
        private:
            //static unsigned int m_idTotal_colonist;
            //unsigned int m_id_colonist;

            std::string m_name_colonist;
            //unsigned short int m_age_colonist;
            //unsigned short int m_health_colonist;
            //unsigned short int m_nunger_colonist;
            //unsigned short int m_mood_colonist;
            //unsigned int m_daysLived_colonist;

            //bool m_aliveStatus_colonist;
            //colonist* m_colonist_colonist;
            //withland::components::gender m_genger_colonist;
            //withland::components::race m_race_colonist;
            withland::components::profession m_profession_colonist;
            //withland::components::disease m_disease_colonist;


        public:
            colonist(std::string name_);
            ~colonist();
            std::string GetName();
            withland::components::profession GetProfession() { return m_profession_colonist; }
        };
    }
}

#endif