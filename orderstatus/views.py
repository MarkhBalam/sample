from django.shortcuts import render

# Create your views here.
def orderstatus(request):
  return render(request,'orderstatus/order-status.html')