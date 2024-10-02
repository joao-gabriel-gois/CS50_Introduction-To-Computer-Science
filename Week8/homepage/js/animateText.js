//const sigmf = (x) => {
//  const euler = 2.71828;
//  return (
//    1 / (1 + euler ** (-x))
//  );
//}
let latestRmTimeout;
let triggeredTimeouts = [];
let previousText, previousEl;
export const animateText = (element, duration = 3, accel = 1, isRemoveable = true) => {
  const currentElement = element;
  let finalContent = currentElement.innerText.split('');
  let innerText = currentElement.innerText + ' ';
  init();
  
  function init() {
    currentElement.innerText = '';
    // (*1) check style display style for p
    // currentElement.style.display = 'inherit';
    let i = 0, j = 0, easeRatio = 0;
    const avgDurationPerLetter = (duration * 1000 / accel) / innerText.length;

    if (isRemoveable && triggeredTimeouts.length > 0) {
      triggeredTimeouts.forEach(timeout => clearTimeout(timeout));
      if (previousEl.tagName === 'P') previousEl.innerText = previousText;
    }

    for (let letter of innerText) {
      easeRatio += ease(i * avgDurationPerLetter) * (avgDurationPerLetter + duration);
      const iterationTimeout = setTimeout(() => {
        if (currentElement.children[j - 1]) currentElement.children[j - 1].classList.remove('latest');
        currentElement.innerHTML += `<span>${letter}</span>`;
        currentElement.children[j].classList.add('latest');
        j++;
      }, easeRatio);
      if (currentElement.tagName === 'P') triggeredTimeouts.push(iterationTimeout);
      i++;
    }

    triggeredTimeouts.push(
      setTimeout(() => {
        finalContent.push('<span class="latest"> </span>');
        finalContent = finalContent.join('');
        currentElement.innerHTML = finalContent;
        if (isRemoveable) {
          if (latestRmTimeout) clearTimeout(latestRmTimeout);
          latestRmTimeout = setTimeout(() => currentElement.querySelector('.latest').remove(), 4800);
        }
        triggeredTimeouts = [];
      }, easeRatio + 120)
    );

    previousEl = currentElement;
    previousText = innerText;

    function ease(time) {
      return (1 - Math.cos(time * Math.PI)) / 2;
    };
  }
}
