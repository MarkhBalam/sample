from django.http import HttpResponseRedirect
from django.shortcuts import render,redirect
from .models import Add_Product

# Create your views here.
def homepage(request):

    return render(request,"homepage/index.html",{
      "products": Add_Product.objects.all()  
    })

def addproduct(request):
    if request.method =="POST":
        category = request.POST['category']
        productImage = request.FILES['productImage']
        productName = request.POST['productName']
        price = request.POST['price']
        discount= request.POST['discount']
        description = request.POST['description']

        new_product = Add_Product.objects.create(
            category=category,
            productImage = productImage,
            productName=productName,
            price=price,
            discount=discount,
            description=description
            
        )
        new_product.save()
        
        # Redirect to a success page or wherever you need
        #return HttpResponseRedirect('homepage/index.html')
        return redirect('homepage')

    return render(request,"homepage/add-product.html",{})
def index(request):
    return render(request, 'index.html')