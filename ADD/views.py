from django.shortcuts import render

# Create your views here.
def add(request):
      return render(request, 'add-product.html')

def order(request):
      return render(request, 'order-status.html')