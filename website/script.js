function save_data() {
    // Get input values
    var name = document.getElementById('nameInput').value;
    var email = document.getElementById('emailInput').value;
    var message = document.getElementById('messageInput').value;

    // Log the data (you can replace this with your desired functionality)
    console.log('Name:', name);
    console.log('Email:', email);
    console.log('Message:', message);

    
    if (name == '' || email == '' || message == ''){
        document.getElementById('send-msg').innerHTML = "Fill all details to submit form ";
    }else {
        document.getElementById('nameInput').value = '';
        document.getElementById('emailInput').value = '';
        document.getElementById('messageInput').value = '';
        document.getElementById('send-msg').innerHTML = "Thank you for your message! We'll get back to you soon.";
    }
}
function scrollToAbout() {
    var aboutSection = document.getElementById('about');
    if (aboutSection) {
      aboutSection.scrollIntoView({ behavior: 'smooth' });
    }
}
function scrollToParameters() {
    var aboutSection = document.getElementById('parameters');
    if (aboutSection) {
      aboutSection.scrollIntoView({ behavior: 'smooth' });
    }
}
function scrollTomonitoringsystem() {
    var aboutSection = document.getElementById('monitoring-system');
    if (aboutSection) {
      aboutSection.scrollIntoView({ behavior: 'smooth' });
    }
}
function scrollTocomponents() {
    var aboutSection = document.getElementById('components');
    if (aboutSection) {
      aboutSection.scrollIntoView({ behavior: 'smooth' });
    }
}
function scrollTocontact() {
    var aboutSection = document.getElementById('contact');
    if (aboutSection) {
      aboutSection.scrollIntoView({ behavior: 'smooth' });
    }
}

async function fetchAndUpdateValues() {
    try {
        const response = await fetch('https://api.thingspeak.com/channels/2388915/feeds.json?results=1');
        const data = await response.json();
        const latestEntry = data.feeds[0];
        document.getElementById('temperature').innerText = `Temperature: ${latestEntry.field1} °C`;
        document.getElementById('water-quality').innerText = `Water Quality: ${latestEntry.field2}`;
    } catch (error) {
        console.error('Error fetching data:', error);
    }
    }

const observer = new IntersectionObserver(entries => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.classList.add('in-viewport');
        }
    });
}, {
    threshold: 0.5,
});

document.querySelectorAll('section').forEach(section => {
    observer.observe(section);
});



window.onload = fetchAndUpdateValues;
  
  
setInterval(fetchAndUpdateValues, 1000);