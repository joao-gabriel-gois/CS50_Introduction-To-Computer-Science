import { animateText } from './js/animateText.js';

const h1 = document.querySelector('h1');
animateText(h1, 2.75, 1, false);
setTabContentChangeEvent(animateText);

function setTabContentChangeEvent(callback) {
  const targetNode = document.getElementById("tab-content");
  // Animating first visible tab content
  callback(document.getElementById('about-tab-pane').children[0]);
  const config = { attributes: true, childList: true, subtree: true };
  const mutationCallback = (mutationList, observer) => {
    const lastMutatedBSClass = "tab-pane fade active show";
    for (const mutation of mutationList) {
      // The string bellow represent the last mutation of the class of the destination tab
      if (mutation.target.className === lastMutatedBSClass) {
        [...mutation.target.children].forEach(p => {
          if (p.tagName === 'P') {
            callback(p, 2.75, 1.1);
          }
        });
      }
    }
  };

  const observer = new MutationObserver(mutationCallback);
  observer.observe(targetNode, config);

  return observer.disconnect;
}
