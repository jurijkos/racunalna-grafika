const WIDTH = 700
const HEIGHT = 600
const PI = Math.PI
let count = true
let difficulty
let requestId
let stoped = false
let canvas, ctx, keystate, menu, winText
let player, ai, ball
let aiResult = 0,
  playerResult = 0
keystate = {
  up: false,
  down: false,
}

player = {
  x: null,
  y: null,
  width: 20,
  height: 100,
  update: function() {
    if (keystate.up && this.y > 0) {
      this.y = this.y - 5
    }
    if (keystate.down && this.y < HEIGHT - this.height) {
      this.y = this.y + 5
    }
  },
  draw: function() {
    ctx.fillRect(this.x, this.y, this.width, this.height)
  },
}
ai = {
  x: null,
  y: null,
  width: 20,
  height: 100,
  direction: 5,
  update: function() {
    const destination = ball.y - (this.height - ball.side) / 2
    switch (difficulty) {
      case 1:
        if (this.y < 10) {
          this.direction = 5
        }
        if (this.y > HEIGHT - this.height - 10) {
          this.direction = -5
        }
        this.y = this.y + this.direction
        break
      case 2:
        this.y += (destination - this.y) * 0.1
        break
      case 3:
        this.y += (destination - this.y) * 0.3
        break
    }
    this.y = Math.max(Math.min(this.y, HEIGHT - this.height), 0)
  },
  draw: function() {
    ctx.fillRect(this.x, this.y, this.width, this.height)
  },
}
ball = {
  x: null,
  y: null,
  side: 20,
  speed: null,
  maxSpeed: 10,
  serve: function(side) {
    const r = Math.random()
    this.x = side === 1 ? player.x + player.width : ai.x - this.side
    this.y = (HEIGHT - this.side) * r
    // calculate out-angle, higher/lower on the y-axis =>
    // steeper angle
    const phi = 0.1 * PI * (1 - 2 * r)
    // set velocity direction and magnitude
    this.speed = {
      x: side * this.maxSpeed * Math.cos(phi),
      y: this.maxSpeed * Math.sin(phi),
    }
  },
  update: function() {
    this.x = this.x + this.speed.x
    this.y = this.y + this.speed.y
    if (this.y < 0 || this.y > HEIGHT - this.side) {
      const offset =
        this.speed.y < 0 ? 0 - this.y : HEIGHT - (this.y + this.side)
      this.y += 2 * offset
      this.speed.y = -1 * this.speed.y
    }
    const isIntersect = function(ax, ay, aw, ah, bx, by, bw, bh) {
      return ax < bx + bw && ay < by + bh && bx < ax + aw && by < ay + ah
    }
    let racquet = this.speed.x < 0 ? player : ai
    if (
      isIntersect(
        racquet.x,
        racquet.y,
        racquet.width,
        racquet.height,
        ball.x,
        ball.y,
        ball.side,
        ball.side
      )
    ) {
      this.x = racquet === player ? player.x + player.width : ai.x - this.side
      const n = (this.y + this.side - racquet.y) / (racquet.height + this.side)
      const phi = 0.25 * PI * (2 * n - 1) // pi/4 = 45
      const smash = Math.abs(phi) > 0.2 * PI ? 1.5 : 1
      this.speed.x =
        smash * (racquet === player ? 1 : -1) * this.maxSpeed * Math.cos(phi)
      this.speed.y = smash * this.maxSpeed * Math.sin(phi)
    }
    if (ball.x < 0 - ball.side || ball.x > WIDTH) {
      if (ball.x < 0) {
        aiResult++
      } else {
        playerResult++
      }
      if (
        (aiResult > 10 || playerResult > 10) &&
        Math.abs(aiResult - playerResult) >= 2
      ) {
        if (playerResult > aiResult) {
          winText.innerHTML = 'Pobjedili ste'
        } else {
          winText.innerHTML = 'Izgubili ste'
        }
        window.cancelAnimationFrame(requestId)
        resetGame()
      } else {
        count = false
        setTimeout(() => {
          this.serve(ball.x < 0 ? 1 : -1)
          count = true
        }, 1000)
        
      }
    }
  },
  draw: function() {
    ctx.fillRect(this.x, this.y, this.side, this.side)
  },
}

const update = () => {
  ball.update()
  ai.update()
  player.update()
}

const draw = () => {
  ctx.fillStyle = '#0066cc'
  ctx.fillRect(0, 0, WIDTH, HEIGHT)
  ctx.font = '50px Georgia'
  ctx.save()
  ctx.fillStyle = 'white'
  ctx.fillText(playerResult, 200, 50)
  ctx.fillText(aiResult, 500, 50)
  ball.draw()
  ai.draw()
  player.draw()

  ctx.fillRect((WIDTH - 2.5) / 2, 0, 5, HEIGHT)

  ctx.restore()
}

const resetGame = () => {
  stoped = true
  aiResult = 0
  playerResult = 0
  menu.style.visibility = 'visible'
  winText.style.visibility = 'visible'
}

const init = () => {
  player.x = player.width
  player.y = (HEIGHT - player.height) / 2.0

  ai.x = WIDTH - (player.width + ai.width)
  ai.y = (HEIGHT - player.height) / 2.0

  ball.x = (WIDTH - ball.side) / 2.0
  ball.y = (HEIGHT - ball.side) / 2.0

  ball.speed = {
    x: -ball.maxSpeed,
    y: 0,
  }
}

const initCanvas = () => {
  canvas = document.createElement('canvas')
  canvas.style.border = '5px solid white'
  canvas.style.position = 'absolute'
  canvas.style.margin = 'auto'
  canvas.style.top = '0'
  canvas.style.bottom = '0'
  canvas.style.left = '0'
  canvas.style.right = '0'

  canvas.width = WIDTH
  canvas.height = HEIGHT
  ctx = canvas.getContext('2d')
  document.body.appendChild(canvas)
  ctx.fillStyle = '#0066cc'
  ctx.fillRect(0, 0, WIDTH, HEIGHT)
}

const initButton = (text, diff) => {
  const button = document.createElement('button')
  button.style.padding = '10px 20px'
  button.style.color = 'white'
  button.style.backgroundColor = '#0066cc'
  button.style.borderRadius = '5px'
  button.style.fontSize = '20px'
  button.style.width = '200px'
  button.style.margin = '40px 100px 0'
  button.style.cursor = 'pointer'
  button.innerHTML = text

  button.onmouseover = () => {
    button.style.backgroundColor = '#003399'
  }
  button.onmouseleave = () => {
    button.style.backgroundColor = '#0066cc'
  }
  button.onclick = () => {
    menu.style.visibility = 'hidden'
    winText.style.visibility = 'hidden'
    stoped = false
    difficulty = diff
    playGame()
  }
  return button
}

const initMenu = () => {
  document.body.style.backgroundColor = '#D3D3D3'
  menu = document.createElement('div')
  menu.style.position = 'absolute'
  menu.style.margin = 'auto'
  menu.style.top = '0'
  menu.style.bottom = '0'
  menu.style.left = '0'
  menu.style.right = '0'
  menu.style.height = '300px'
  menu.style.width = '400px'
  menu.style.backgroundColor = '#D3D3D3'
  menu.style.borderRadius = '6px'
  document.body.appendChild(menu)

  const easy = initButton('Easy', 1)
  menu.appendChild(easy)

  const medium = initButton('Medium', 2)
  menu.appendChild(medium)

  const hard = initButton('Hard', 3)
  menu.appendChild(hard)
  initWinText()
}

const initKeyListeners = () => {
  document.addEventListener('keydown', function(e) {
    if (e.keyCode === 38) {
      keystate.up = true
    }
    if (e.keyCode === 40) {
      keystate.down = true
    }
  })

  document.addEventListener('keyup', function(e) {
    if (e.keyCode === 38) {
      keystate.up = false
    }
    if (e.keyCode === 40) {
      keystate.down = false
    }
  })
}

const initWinText = () => {
  winText = document.createElement('div')
  winText.style.fontSize = '30px'
  winText.style.color = 'white'
  winText.style.position = 'relative'
  winText.style.left = '120px'
  winText.style.top = '-350px'
  winText.style.visibility = 'hidden'
  menu.appendChild(winText)
}

const initGraphics = () => {
  initCanvas()
  initKeyListeners()
  initMenu()
}

const main = () => {
  initGraphics()
}

const playGame = () => {
  init()
  const loop = () => {
    if (count) {
      update()
      draw()
    }
    if (!stoped) {
      requestId = window.requestAnimationFrame(loop)
    }
  }
  window.requestAnimationFrame(loop)
}

main()
