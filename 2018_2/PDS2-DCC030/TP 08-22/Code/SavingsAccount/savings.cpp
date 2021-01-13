#include "savings.h"

float SavingsAccount::annual_savings_rate = 0;

SavingsAccount::SavingsAccount(float savings_balance){
  this->savings_balance = savings_balance;
}

float SavingsAccount::calculate_monthly_balance(){
  this->savings_balance += (this->savings_balance * annual_savings_rate) / 12.0f;
  return this->savings_balance;
}

void SavingsAccount::modify_interest_rate(float savings_rate){
  annual_savings_rate = savings_rate;
}
