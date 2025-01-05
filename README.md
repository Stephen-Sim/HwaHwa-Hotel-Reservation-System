# Price Calculation Logic

## Overview
This sheet calculates the total price based on the selected room type, meal plan, and number of nights. Additionally, it includes an admin login feature and categorizes customers into tiers based on their total spending.

---

## Room Type Prices
- **Single Room**: 50  
- **Double Room**: 100  
- **Deluxe Room**: 150  
- **Family Room**: 200  
- **Presidential Room**: 250  

---

## Meal Plan Additions
- **Meal Plan 1**: +30 per night  
- **Meal Plan 2**: +50 per night  
- **No Meal Plan**: +0 per night  

---

## Formula
The total price is calculated using the formula:
(Room Price + Meal Plan Cost) × Number of Nights)


---

## Steps to Use
1. **Input Details**: Enter the number of nights, room type, and meal plan in their respective columns.  
2. **View Total Price**: The formula in the `total_price` column will automatically compute the final amount.  

---

## Example
- **Room Type**: Deluxe Room (150 per night)  
- **Meal Plan**: Meal Plan 1 (+30 per night)  
- **Number of Nights**: 3  

### Calculation:
1. **Room Price**: 150 per night  
2. **Meal Plan Cost**: 30 per night  
3. **Total for One Night**: `150 + 30 = 180`  
4. **Total Price**: `180 × 3 = 540`

**Final Total Price**: **540**

---

## Admin Login
This sheet includes an **Admin Login** feature for managing data securely.

- **Username**: `admin`  
- **Password**: `abc123`  

---

## Customer Tier System
Customers are categorized into tiers based on their total spending:

### Tier Criteria:
- **Platinum Tier Customer**: Spending ≥ 3000  
- **Gold Tier Customer**: Spending ≥ 2000 but < 3000  
- **Silver Tier Customer**: Spending ≥ 1000 but < 2000  
- **Bronze Tier Customer**: Spending < 1000  
