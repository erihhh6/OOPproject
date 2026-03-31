/// constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

/// Garden layout
static constexpr int MAX_SLOTS = 8;

/// Default daily decay rates (base values, overridden per plant type)
static constexpr int DAILY_WATER_DECAY      = 10;
static constexpr int DAILY_FERTILIZER_DECAY = 2;
static constexpr int DAILY_LIGHT_DECAY      = 1;

/// Season system: one new season every N days
static constexpr int DAYS_PER_SEASON = 10;

/// Growth stage advancement: consecutive healthy days required per stage
static constexpr int DAYS_TO_GROW_SEEDLING = 3;
static constexpr int DAYS_TO_GROW_GROWING  = 5;
static constexpr int DAYS_TO_GROW_MATURE   = 7;

/// Minimum health % required for growth stage advancement
static constexpr double GROWTH_HEALTH_THRESHOLD = 70.0;

/// Ratio below which a resource triggers plant death (current < needed * DEATH_RATIO)
static constexpr double DEATH_RATIO = 0.5;

#endif /// CONSTANTS_H
