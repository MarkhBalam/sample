from django.shortcuts import render

# Create your views here.
from django.shortcuts import render

def home_view(request):
    # Define your product data
    products = [
        {"name": "Watch", "image": "watch.jpg", "price": 99.99, "discount": 10, "rating": 4},
        {"name": "Shoes", "image": "shoes.jpg", "price": 49.99, "discount": 5, "rating": 3},
        {"name": "Shirt", "image": "shirt.jpg", "price": 29.99, "discount": 15, "rating": 2},
        # Add more products here
    ]
    
    return render(request, "home.html", {"products": products})
