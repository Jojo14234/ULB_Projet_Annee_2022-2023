#pragma once

const int MAX_USERNAME_SIZE = 32;
const int MAX_PASSWORD_SIZE = 62;

const int EMPTY_DATABASE_RESERVE_SPACE = 10;
const double RESERVE_SPACE_SUPP = 0.4; // Espace mémoire alloué en plus pour la db lors de son chargement

// User
constexpr int MAX_FRIENDS = 20;
constexpr int MAX_REQUESTS = 20;