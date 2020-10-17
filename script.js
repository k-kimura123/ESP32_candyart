let penColor = 'white';

//Carousel
const carouselSlide = document.querySelector('.carousel-slide');
const carouselImages = document.querySelectorAll('.carousel-slide img');
const prevBtn = document.querySelector('#prevBtn');
const nextBtn = document.querySelector('#nextBtn');
let counter = 1;
const size = carouselImages[0].naturalWidth;

carouselSlide.style.transform = 'translateX(' + (-size * counter) + 'px)';

carouselSlide.addEventListener('transitionend',() => {
    if(carouselImages[counter].id === 'lastClone'){
        carouselSlide.style.transition = "none";
        counter = carouselImages.length - 2;
        carouselSlide.style.transform = 'translateX(' + (-size * counter) + 'px)';
    }
    if(carouselImages[counter].id === 'firstClone'){
        carouselSlide.style.transition = "none";
        counter = carouselImages.length - counter;
        carouselSlide.style.transform = 'translateX(' + (-size * counter) + 'px)';
    }
});

function carousel_next(){
    console.log("carousel_next works")
    if (counter >= carouselImages.length - 1) return;
    carouselSlide.style.transition = "transform 0.5s ease-in-out";
    counter++;
    carouselSlide.style.transform = 'translateX(' + (-size * counter) + 'px)';
}

function carousel_prev(){
    if (counter <= 0) return;
    carouselSlide.style.transition = "transform 0.5s ease-in-out";
    counter--;
    carouselSlide.style.transform = 'translateX(' + (-size * counter) + 'px)';
}

function setPenColor(chosen_color){
    penColor = chosen_color;
}
function setPixelColor(pixel){
    pixel.style.backgroundColor = penColor
    
}

function clearCanvas(){
    let pixels = document.getElementById("pixelcanvas").getElementsByClassName("pixel");
    for(i = 0; i < pixels.length; i++){
        pixels[i].style.backgroundColor = 'white'
    }
}

function getPixelArray(){
    let pixelarray = []
    let pixels = document.getElementById("pixelcanvas").getElementsByClassName("pixel");
    for(i = 0; i < pixels.length; i++){
        if(!pixels[i].style.backgroundColor){
            pixels[i].style.backgroundColor = 'white'
        }
        pixelarray.push(pixels[i].style.backgroundColor)
    }
    console.log(pixelarray)
}
