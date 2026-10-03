//  entityStates.hpp (WithLand Core)
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
#ifndef withland_entityStates_hpp
#define withland_entityStates_hpp

#include <withland/common/common.hpp>


namespace withland {
    namespace components {
        enum class gender { Male, Female, COUNT };
        
        enum class race { Human, Elf, Orc, Vampire, COUNT };

        enum class profession {
            Warrior,       // Воин
            Rogue,         // Разбойник (Плут)
            Ranger,        // Следопыт (Охотник)
            Monk,          // Монах
            Paladin,       // Паладин
            Bard,          // Бард
            Mage,          // Маг
            Priest,        // Жрец (Клирик)
            Warlock,       // Чернокнижник
            Druid,         // Друид
            Blacksmith,    // Кузнец
            Alchemist,     // Алхимик
            Engineer,      // Инженер
            Leatherworker, // Кожевник
            Tailor,        // Портной (Ткач)
            Merchant,      // Торговец
            COUNT
        };
        
        enum class disease {
            None,            // Здоров (Нет болезни)
            
            // Классические и исторические болезни
            Plague,          // Чума
            Cholera,         // Холера
            Leprosy,         // Проказа
            Fever,           // Лихорадка
            Rabies,          // Бешенство
            Dysentery,       // Дизентерия
            
            // Фэнтезийные и магические недуги
            ManaBurn,        // Выгорание маны
            StoneCurse,      // Каменное проклятие (Окаменение)
            BloodRot,        // Гниль крови
            Vampirism,       // Вампиризм
            Lycanthropy,     // Ликантропия (Оборотничество)
            VoidSickness,    // Скверна Бездны / Болезнь Бездны
            GloomWrack,      // Некротическая хворь / Мрак
            
            // Психические расстройства и эффекты разума
            Paranoia,        // Паранойя
            Insanity,        // Безумие
            Hysteria,        // Истерия
            COUNT
        };

        const std::vector<std::string> male_names_colonist;

        const std::vector<std::string> female_names_colonist;
    }
}

#endif