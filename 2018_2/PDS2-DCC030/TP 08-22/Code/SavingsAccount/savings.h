#ifndef PDS2_SAVINGS_H
#define PDS2_SAVINGS_H

class SavingsAccount{
  private:
  float savings_balance;

  public:
  static float annual_savings_rate;

  SavingsAccount(float savings_balance);

  float calculate_monthly_balance();
  static void modify_interest_rate(float interest_rate);
};

#endif
