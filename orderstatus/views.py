

from django.shortcuts import render
from .models import Order, OrderStatus

# Create your views here.
def orderstatus(request):
  return render(request,'orderstatus/order-status.html')
  

def order_list(request):
    orders = Order.objects.all()
    return render(request, 'order_list.html', {'orders': orders})

def order_detail(request, order_id):
    order = Order.objects.get(id=order_id)
    order_statuses = OrderStatus.objects.filter(order=order)
    return render(request, 'order_detail.html', {'order': order, 'order_statuses': order_statuses})
